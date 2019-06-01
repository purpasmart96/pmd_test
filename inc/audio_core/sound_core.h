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

#ifndef _SOUND_CORE_H_
#define _SOUND_CORE_H_

#include "audio_core/al_common.h"

typedef struct Stack Stack;


// 16 bit Stereo
#define SFX_MAX_SOURCE          1
#define MAX_BUFFERS             512
#define MAX_SAMPLES             256
#define MAX_SOURCES             16
#define STEREO_CHANNELS         2
#define SIZE_SHORT              2
#define SIZE_FLOAT              4   // size of a float in bytes

typedef struct SoundSource
{
    ALuint source;
    ALint source_state;
    FILE *file;
} SoundSource;

typedef struct SoundCore
{
    ALenum     format;
    ALsizei    size;
    ALsizei    freq;
    ALboolean  loop;
    ALvoid     *data;
    ALCdevice  *device;
    ALCcontext *context;
    SoundSource sources[MAX_SOURCES];
    ALuint buffers[MAX_BUFFERS];
    bool seprate_thread;
    float master_volume;
    HANDLE thread_handle;

} SoundCore;

typedef struct SoundInfo
{
    int freqency; //sound frequency (eg. 44100 Hz)
    int channels; //nunber of channels (eg. Stereo = 2)
    int bits_per_channel; //number of bits per channel (eg. 16 for 2 channel stereo)
    int size;
    char *buffer_data;
} SoundInfo;

//int ogg_decode(const char *file_name, const char *file_name_out);
SoundInfo *ogg_decode(const char *file_name);
//int ogg_decode(const char *file_name, char *raw_pcm_out);
SoundInfo *SoundInfo_New(int freqency, int channels, int bits_per_channel, Stack *buffer, int size);

#endif


