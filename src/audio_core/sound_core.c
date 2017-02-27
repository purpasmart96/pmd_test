// Copyright(c) <2015> <Purpasmart>
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

#include "audio_core/al_common.h"
#include "audio_core/sound_core.h"
#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>

#include <ogg/os_types.h>
#include <ogg/ogg.h>

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
