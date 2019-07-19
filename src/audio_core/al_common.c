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

#include "audio_core/sound_core.h"
#include "audio_core/al_common.h"
#if defined(__GNUC__)
#include <pthread.h>
#elif defined(_MSC_VER)
#include <ProcessThreadsAPI.h>
#endif

ALState *ALState_New(int buffer_count, bool seprate_thread, bool init_sources)
{
    ALState *al = (ALState*) malloc(sizeof(*al));

    if (!al)
    {
        return NULL;
    }

    ALState_Init(al, buffer_count, seprate_thread, init_sources);

    return al;
}

void ALState_Delete(ALState *self)
{
    alDeleteBuffers(self->buffer_count, &self->buffers);
    alcDestroyContext(self->context);
    alcCloseDevice(self->device);
    free(self);
}

void ALState_SetSource(ALState *self)
{
    alGenSources(self->buffer_count, &self->source);
}

#if defined(__GNUC__)
void* ALState_UpdateThread(void* uncasted_self)
{
    ALState* self = (ALState*) uncasted_self;
    while (true)
    {
        alGetSourcei(self->source, AL_SOURCE_STATE, &self->source_state);
        if (self->source_state != AL_PLAYING)
        {
            alSourcePlay(self->source);
        }
    }
    return 0;
}
#elif defined(_MSC_VER)
DWORD WINAPI ALState_UpdateThread(ALState *self,  __in LPVOID lpParameter)
{
    while (true)
    {
        alGetSourcei(self->source, AL_SOURCE_STATE, &self->source_state);
        if (self->source_state != AL_PLAYING)
        {
            alSourcePlay(self->source);
        }
    }
    return 0;
}
#endif

static void list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    DEBUG("Devices list:\n");
    DEBUG("----------\n");
    while (device && *device != '\0' && next && *next != '\0')
    {
        DEBUG("%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    DEBUG("----------\n");
}

void ALState_Init(ALState *self, int buffer_count, bool seprate_thread, bool init_sources)
{
#if 0
    alGetError();
    self->buffer_count = buffer_count;
    self->device = alcOpenDevice(NULL);

    if (!self->device)
    {
        ERROR("OpenAL Device Failed To Open!\n");
        return;
    }

    self->context = alcCreateContext(self->device, NULL);

    if (!alcMakeContextCurrent(self->context))
    {
        ERROR("OpenAL Context Error: %d\n", alGetError());
        return;
    }

    //CreateThread(NULL, 0, althread, NULL, 0, NULL);
    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListener3f(AL_ORIENTATION, 0, 0, -1);

    //alGenSources(self->buffer_count, &self->source);
    alGenSources((ALuint)1, &self->source);

    alSourcef(self->source, AL_PITCH, 1);
    alSourcef(self->source, AL_GAIN, 1);
    alSource3f(self->source, AL_POSITION, 0, 0, 0);
    alSource3f(self->source, AL_VELOCITY, 0, 0, 0);
    alSourcei(self->source, AL_LOOPING, AL_FALSE);

    // Create the buffers
    //alGenBuffers(self->buffer_count, &self->buffers);
    alGenBuffers((ALuint)1, &self->buffers);

    if (seprate_thread)
    {
        #if defined(__GNUC__)
        #elif defined(_MSC_VER)
        #endif
        CreateThread(NULL, 0, ALState_UpdateThread, NULL, 0, NULL);
    }
#endif
}

static ALenum to_al_format(int channels, int samples)
{
    bool stereo = (channels > 1);

    switch (samples)
    {
        case 16:
        {
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        }
        case 8:
        {
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        }
        default:
            return -1;
    }
}

void AL_State_LoadBuffer(ALState *self)
{
    SoundInfo *sound_info = NULL;
    alGetError();
    ALCdevice *device = alcOpenDevice(NULL);
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    ALCcontext *context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context))
        ERROR("Al context failed to init!\n");

    ALuint source;
    alGenSources((ALuint)1, &source);
    // check for errors

    alSourcef(source, AL_PITCH, 1);
    // check for errors
    alSourcef(source, AL_GAIN, 1);
    // check for errors
    alSource3f(source, AL_POSITION, 0, 0, 0);
    // check for errors
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    // check for errors
    alSourcei(source, AL_LOOPING, AL_FALSE);
    // check for errros
    ALuint buffer;
    alGenBuffers((ALuint)1, &buffer);

    ALuint source_state;

    sound_info = ogg_decode("D:/PokeMysteryDun/pmd_fix/data/sound/bgm/Icicle Forest.ogg");
    if (sound_info != NULL)
    {
        alBufferData(buffer, to_al_format(sound_info->channels, sound_info->bits_per_channel), sound_info->buffer_data, sound_info->size, sound_info->freqency);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        // check for errors
        while (source_state == AL_PLAYING)
        {
            alGetSourcei(source, AL_SOURCE_STATE, &source_state);
            // check for errors
        }
    }
    else
    {
        ERROR("Failed To Decode Ogg File\n");
    }

    DEBUG("ALBuffer is now set up\n");
}