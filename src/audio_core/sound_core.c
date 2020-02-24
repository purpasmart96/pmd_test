// Copyright(c) 2015 <Purpasmart>
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "common/strlcat.h"
#include "common/stack.h"
#include "audio_core/al_common.h"
#include "audio_core/sound_core.h"

#include <ogg/os_types.h>
#include <ogg/ogg.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>


#include <io.h>
#include <fcntl.h>

static ALuint current_source = 0;
static ALuint next_source = 1;

static ALuint IncrementSource()
{
    next_source++;
    return current_source++;
}

static ALuint DecrementSource()
{
    next_source--;
    return current_source--;
}

SoundCore *SoundCore_New(bool seprate_thread, bool init_sources)
{
    SoundCore *sound_core = malloc(sizeof(*sound_core));

    if (!sound_core)
    {
        return NULL;
    }

    alGetError();
    sound_core->device = alcOpenDevice(NULL);
    sound_core->context = alcCreateContext(sound_core->device, NULL);
    alcMakeContextCurrent(sound_core->context);
    //CreateThread(NULL, 0, althread, NULL, 0, NULL);
    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListener3f(AL_ORIENTATION, 0, 0, -1);


    //alSourcef(sound_core->source, AL_PITCH, 1);
    //alSourcef(sound_core->source, AL_GAIN, 1);
    //alSource3f(sound_core->source, AL_POSITION, 0, 0, 0);
    //alSource3f(sound_core->source, AL_VELOCITY, 0, 0, 0);
    //alSourcei(sound_core->source, AL_LOOPING, AL_FALSE);

    // Create the buffers
    //alGenBuffers(sound_core->buffer_count, &sound_core->buffers);

    return sound_core;
}

void SoundCore_Delete(SoundCore *self)
{
    alDeleteBuffers(MAX_BUFFERS, self->buffers);
    alcDestroyContext(self->context);
    alcCloseDevice(self->device);
    WaitForSingleObject(self->thread_handle, INFINITE);
    free(self);
}

void SoundCore_SetSource(SoundCore *self)
{
	//alGenSources(self->buffer_count, &self->source);
}

DWORD WINAPI SoundCore_UpdateThread(SoundCore *self,  __in LPVOID lpParameter)
{
    while (true)
    {
        alGetSourcei(self->sources[current_source].source, AL_SOURCE_STATE, self->sources[current_source].source_state);
        if (self->sources[current_source].source_state != AL_PLAYING)
        {
            alSourcePlay(self->sources[IncrementSource()].source);
        }
    }
    return 0;

}

//void *SoundCore_UpdateThread(SoundCore *self, void *param)
//{
//    alGetSourcei(self->sources[current_source].source, AL_SOURCE_STATE, self->sources[current_source].source_state);
//    if (self->sources[current_source].source_state != AL_PLAYING)
//    {
//        alSourcePlay(self->sources[IncrementSource()].source);
//    }
//}


void SoundCore_Init(SoundCore *self)
{
    alGenBuffers(MAX_BUFFERS, self->buffers);
    alGenSources(MAX_SOURCES, self->sources);


    if (self->seprate_thread)
    {
        self->thread_handle = CreateThread(NULL, 0, SoundCore_UpdateThread, NULL, 0, NULL);
    }

}

void SoundCore_Decode(SoundCore *self, const char *sound_name)
{
    self->sources[current_source].file = fopen(sound_name, "rb");
}

void SoundCore_PlaySound(SoundCore *self, const char *sound_name, ALboolean loop)
{
    alSourcef(self->sources[current_source].source, AL_PITCH, 1);
    alSourcef(self->sources[current_source].source, AL_GAIN, 1);
    alSource3f(self->sources[current_source].source, AL_POSITION, 0, 0, 0);
    alSource3f(self->sources[current_source].source, AL_VELOCITY, 0, 0, 0);
    alSourcei(self->sources[current_source].source, AL_LOOPING, loop);
    alSourcePlay(self->sources[IncrementSource()].source);
}

void SoundCore_SetMasterVolume(SoundCore *self, float volume)
{
    self->master_volume = CLAMP(0.0f, 1.0f, volume);
    alListenerf(AL_GAIN, self->master_volume);
}

float SoundCore_GetMasterVolume(SoundCore *self)
{
    return self->master_volume;
}

SoundInfo *SoundInfo_New(int freqency, int channels, int bits_per_channel, Stack *buffer, int size)
{
    SoundInfo *sound_info = malloc(sizeof(*sound_info));

    if (!sound_info)
    {
        return NULL;
    }


    sound_info->freqency = freqency;
    sound_info->channels = channels;
    sound_info->bits_per_channel = bits_per_channel;
    sound_info->buffer_data = malloc(buffer->size * 4096 * 2);

    //for (int i = 0; i < buffer->size; i++)
    //{
    //    for (int j = 0; j < 4096; j++)
    //    {
    //        sound_info->buffer_data[j] = buffer->data[i];
    //    }

    //}


    sound_info->size = size;

    return sound_info;
}

static char *concat(const char *s1, const char *s2)
{
    size_t size = strlen(s1) + strlen(s2) + 1;
    char *result = malloc(size);//+1 for the null-terminator
                                                       //in real code you would check for errors in malloc here
    strlcpy(result, s1, size);
    strlcat(result, s2, size);
    return result;
}

SoundInfo *SoundInfo_LoadOGG(const char *filename, ALuint pDestAudioBuffer)
{
    OggVorbis_File oggfile;
    SoundInfo *sound_info = NULL;


    if (ov_fopen(filename, &oggfile))
    {
        ERROR("ov_fopen failed.\n");
        return false;
    }

    vorbis_info *info = ov_info(&oggfile, -1);

    ALenum format;
    switch (info->channels)
    {
        case 1:
            format = AL_FORMAT_MONO16; break;
        case 2:
            format = AL_FORMAT_STEREO16; break;
        case 4:
            format = alGetEnumValue("AL_FORMAT_QUAD16"); break;
        case 6:
            format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
        case 7:
            format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
        case 8:
            format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
        default:
            format = 0; break;
    }

    Stack *samples = stack_new(0x500000);
    //std::vector<int16> samples;
    char tmpbuf[4096];
    int section = 0;
    bool first_run = true;
    while(true)
    {
        int result = ov_read(&oggfile, tmpbuf, 4096, 0, 2, 1, &section);
        if (result > 0)
        {
            first_run = false;
            stack_push(samples, tmpbuf);
                //insert(const_iterator position, size_type n, const value_type& val);
            //samples.insert(samples.end(), tmpbuf, tmpbuf + (result));
        }
        else
        {
            if (result < 0)
            {
                ERROR("Loading ogg sound data failed!\n");
                ov_clear(&oggfile);
                return false;
            }
            else
            {
                if (first_run)
                    return false;
                break;
            }
        }
    }

    sound_info = SoundInfo_New(info->rate, info->channels, 16, samples, oggfile.pcmlengths);
    //alBufferData(pDestAudioBuffer, format, samples->data[0], ov_pcm_total(&oggfile, -1), info->rate);

    //return true;
    return sound_info;
}