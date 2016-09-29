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


ALState *ALState_New(int buffer_count, bool seprate_thread, bool init_sources)
{
    ALState *al = (ALState*)malloc(sizeof(*al));

    if (!al)
    {
        return NULL;
    }

    alGetError();
    al->buffer_count = buffer_count;
    al->device = alcOpenDevice(NULL);
    al->context = alcCreateContext(al->device, NULL);
    alcMakeContextCurrent(al->context);
    //CreateThread(NULL, 0, althread, NULL, 0, NULL);
    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListener3f(AL_ORIENTATION, 0, 0, -1);

    alGenSources(al->buffer_count, &al->source);

    alSourcef(al->source, AL_PITCH, 1);
    alSourcef(al->source, AL_GAIN, 1);
    alSource3f(al->source, AL_POSITION, 0, 0, 0);
    alSource3f(al->source, AL_VELOCITY, 0, 0, 0);
    alSourcei(al->source, AL_LOOPING, AL_FALSE);

    // Create the buffers
    alGenBuffers(al->buffer_count, &al->buffers);

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

void ALState_Init(ALState *self)
{

    if (self->seprate_thread)
    {
        CreateThread(NULL, 0, ALState_UpdateThread, NULL, 0, NULL);
    }

}

