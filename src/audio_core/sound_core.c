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
#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>

#include <ogg/os_types.h>
#include <ogg/ogg.h>

#include <stdlib.h>
#include <fcntl.h>

#if defined(_MSC_VER)
#include <io.h>
#endif
#include <pthread.h>

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
    SoundCore *sound_core = (SoundCore*) malloc(sizeof(*sound_core));

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
#if defined(__GNUC__)
    pthread_join(self->thread_handle, NULL);
#elif defined(_MSC_VER)
    WaitForSingleObject(self->thread_handle, INFINITE);
#endif
    free(self);
}

void SoundCore_SetSource(SoundCore *self)
{
	//alGenSources(self->buffer_count, &self->source);
}
#if defined(__GNUC__)
void* SoundCore_UpdateThread(void* uncasted_self)
{
    SoundCore* self = (SoundCore*) uncasted_self;
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
#elif defined(_MSC_VER)
DWORD WINAPI SoundCore_UpdateThread(SoundCore *self,  __in LPVOID lpParameter)
{
    while (true)
    {
        alGetSourcei(self->sources[current_source].source, AL_SOURCE_STATE, self->sources[current_source].source_state);
        if (self->sources[current_source].source_state != AL_PLAYING)__in LPVOID
        {
            alSourcePlay(self->sources[IncrementSource()].source);
        }
    }
    return 0;

}
#endif

void SoundCore_Init(SoundCore *self)
{
    alGenBuffers(MAX_BUFFERS, self->buffers);
    alGenSources(MAX_SOURCES, self->sources);


    if (self->seprate_thread)
    {
#if defined(__GNUC__)
        pthread_create(&(self->thread_handle), NULL, SoundCore_UpdateThread, (void*) self);
#elif defined(_MSC_VER)
        self->thread_handle = CreateThread(NULL, 0, SoundCore_UpdateThread, NULL, 0, NULL);
#endif
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
    SoundInfo *sound_info = (SoundInfo*) malloc(sizeof(*sound_info));

    if (!sound_info)
    {
        return NULL;
    }


    sound_info->freqency = freqency;
    sound_info->channels = channels;
    sound_info->bits_per_channel = bits_per_channel;
    sound_info->buffer_data = (char*) malloc(buffer->size * 4096 * 2);

    for (int i = 0; i < buffer->size; i++)
    {
        for (int j = 0; j < 4096; j++)
        {
            sound_info->buffer_data[j] = (char*) buffer->data[i];
        }

    }


    sound_info->size = size;

    return sound_info;
}

static char *concat(const char *s1, const char *s2)
{
    size_t size = strlen(s1) + strlen(s2) + 1;
    char *result = (char*) malloc(size);//+1 for the null-terminator
                                                       //in real code you would check for errors in malloc here
    strlcpy(result, s1, size);
    strlcat(result, s2, size);
    return result;
}

SoundInfo *ogg_decode(const char *file_name)
{
    ogg_sync_state   osynch_s; /* sync and verify incoming physical bitstream */
    ogg_stream_state ostream_s; /* take physical pages, weld into a logical
                         stream of packets */
    ogg_page         opg; /* one Ogg bitstream page. Vorbis packets are inside */
    ogg_packet       opck; /* one raw packet of data for decode */

    vorbis_info      vi; /* struct that stores all the static vorbis bitstream
                         settings */
    vorbis_comment   vc; /* struct that stores all the bitstream user comments */
    vorbis_dsp_state vdsp; /* central working state for the packet->PCM decoder */
    vorbis_block     vblck; /* local working space for packet->PCM decode */

    char *buffer;
    int  bytes;

    ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */
    int conv_size = 4096;

    FILE *file;

    if ((file = fopen(file_name, "rb")) == NULL)
    {
        ERROR("File not found!\n");
        return NULL;
    }

    //char *name_out = "_test.wav";
    //char temp_name[0x60];
    //char *stripped_name = NULL;
    //size_t string_size = strlen(file_name) + 1;



    //strlcpy(temp_name, file_name, string_size);
    //stripped_name = strstr(temp_name, ".");
    //
    //char *new_name = concat(stripped_name, name_out);
    //FILE *file_out = fopen("Icicle Forest_test.wav", "wb");
    Stack *bgm_stack = stack_new(0x500000);
    //free(new_name);

    SoundInfo *sound_info = NULL;
    ogg_sync_init(&osynch_s);

    while (true)
    {
        // We repeat if the bitstream is chained
        int eos = 0;
        int i;

        /* grab some data at the head of the stream. We want the first page
        (which is guaranteed to be small and only contain the Vorbis
        stream initial header) We need the first page to get the stream
        serialno. */

        // submit a 4k block to libvorbis' Ogg layer
        buffer = ogg_sync_buffer(&osynch_s, 4096);
        bytes = fread(buffer, 1, 4096, file);
        ogg_sync_wrote(&osynch_s, bytes);

        // Get the first page
        if (ogg_sync_pageout(&osynch_s, &opg) != 1)
        {
            // have we simply run out of data?  If so, we're done.
            if (bytes < 4096)
                break;

            // error case.  Must not be Vorbis data
            ERROR("Input does not appear to be an Ogg bitstream.\n");
        }

        // Get the serial number and set up the rest of decode. 
        // serialno first; use it to set up a logical stream 
        ogg_stream_init(&ostream_s, ogg_page_serialno(&opg));

        /* extract the initial header from the first page and verify that the
        Ogg bitstream is in fact Vorbis data */

        /* I handle the initial header first instead of just having the code
        read all three Vorbis headers at once because reading the initial
        header is an easy way to identify a Vorbis bitstream and it's
        useful to see that functionality seperated out. */

        vorbis_info_init(&vi);
        vorbis_comment_init(&vc);

        if (ogg_stream_pagein(&ostream_s, &opg) < 0)
        {
            /* error; stream version mismatch perhaps */
            ERROR("Error reading first page of Ogg bitstream data.\n");
            return NULL;
        }

        if (ogg_stream_packetout(&ostream_s, &opck) != 1)
        {
            // No page? must not be vorbis 
            ERROR("Error reading initial header packet.\n");
            //return 2;
            return NULL;
        }

        if (vorbis_synthesis_headerin(&vi, &vc, &opck) < 0) {
            ERROR("This Ogg bitstream does not contain Vorbis audio data.\n");
            //return 3;
            return NULL;
        }

        /* At this point, we're sure we're Vorbis. We've set up the logical
        (Ogg) bitstream decoder. Get the comment and codebook headers and
        set up the Vorbis decoder */

        /* The next two packets in order are the comment and codebook headers.
        They're likely large and may span multiple pages. Thus we read
        and submit data until we get our two packets, watching that no
        pages are missing. If a page is missing, error out; losing a
        header page is the only place where missing data is fatal. */

        i = 0;
        while (i < 2)
        {
            while (i < 2)
            {
                int result = ogg_sync_pageout(&osynch_s, &opg);
                if (result == 0)
                    break; /* Need more data */
                                       /* Don't complain about missing or corrupt data yet. We'll
                                       catch it at the packet output phase */
                if (result == 1)
                {
                    ogg_stream_pagein(&ostream_s, &opg); /* we can ignore any errors here
                                                 as they'll also become apparent
                                                 at packetout */
                    while (i < 2)
                    {
                        result = ogg_stream_packetout(&ostream_s, &opck);
                        if (result == 0)
                            break;
                        if (result < 0)
                        {
                            /* Uh oh; data at some point was corrupted or missing!
                            We can't tolerate that in a header.  Die. */
                            ERROR("Corrupt secondary header.  Exiting.\n");
                            return NULL;
                        }
                        result = vorbis_synthesis_headerin(&vi, &vc, &opck);
                        if (result < 0)
                        {
                            ERROR("Corrupt secondary header.  Exiting.\n");
                            return NULL;
                        }
                        i++;
                    }
                }
            }
            // No harm in not checking before adding more
            buffer = ogg_sync_buffer(&osynch_s, 4096);
            bytes = fread(buffer, 1, 4096, file);
            if (bytes == 0 && i < 2)
            {
                ERROR("End of file before finding all Vorbis headers!\n");
                return NULL;
            }
            ogg_sync_wrote(&osynch_s, bytes);
        }

        // Throw the comments plus a few lines about the bitstream we're decoding
        {
            char **ptr = vc.user_comments;
            while (*ptr)
            {
                DEBUG("%s\n", *ptr);
                ++ptr;
            }
            DEBUG("\nBitstream is %d channel, %ldHz\n", vi.channels, vi.rate);
            DEBUG("Encoded by: %s\n\n", vc.vendor);
        }

        conv_size = 4096 / vi.channels;

        // Got and parsed all three headers. Initialize the Vorbis packet->PCM decoder.
        if (vorbis_synthesis_init(&vdsp, &vi) == 0)
        {
            // Central decode state
            vorbis_block_init(&vdsp, &vblck);
            while (!eos)
            {
                while (!eos)
                {
                    int result = ogg_sync_pageout(&osynch_s, &opg);
                    if (result == 0)
                        break;
                    if (result < 0)
                    {
                        // Missing or corrupt data at this page position
                        ERROR("Corrupt or missing data in bitstream. continuing...\n");
                    }
                    else
                    {
                        /* can safely ignore errors at this point */
                        ogg_stream_pagein(&ostream_s, &opg); 
                        while (true)
                        {
                            result = ogg_stream_packetout(&ostream_s, &opck);

                            if (result == 0)
                                /* need more data */
                                break; 
                            if (result < 0)
                            {
                                /* missing or corrupt data at this page position */
                                /* no reason to complain; already complained above */
                            }
                            else
                            {
                                // Decode the packet
                                float **pcm;
                                int samples;

                                if (vorbis_synthesis(&vblck, &opck) == 0)
                                    vorbis_synthesis_blockin(&vdsp, &vblck);
                                /*
                                **pcm is a multichannel float vector.  In stereo, for
                                example, pcm[0] is left, and pcm[1] is right.  samples is
                                the size of each channel.  Convert the float values
                                (-1.<=range<=1.) to whatever PCM format and write it out */

                                while ((samples = vorbis_synthesis_pcmout(&vdsp, &pcm)) > 0)
                                {
                                    int j;
                                    int clip_flag = 0;
                                    int bout = (samples < conv_size ? samples : conv_size);

                                    // Convert floats to 16 bit signed ints (host order) and interleave
                                    for (i = 0; i < vi.channels; i++)
                                    {
                                        ogg_int16_t *ptr = convbuffer + i;
                                        float  *mono = pcm[i];
                                        for (j = 0; j < bout; j++)
                                        {
                                            int val = floor(mono[j] * 32767.f + .5f);
                                            // prevent clipping
                                            if (val > 32767)
                                            {
                                                val = 32767;
                                                clip_flag = 1;
                                            }
                                            if (val < -32768)
                                            {
                                                val = -32768;
                                                clip_flag = 1;
                                            }
                                            *ptr = val;
                                            ptr += vi.channels;
                                        }
                                    }

                                    if (clip_flag)
                                    {
                                        ERROR("Clipping in frame %ld\n", (long)(vdsp.sequence));
                                    }

                                    //char *out_buffer = (char*) malloc(bout);
                                    //memcpy(out_buffer, convbuffer, 2 * vi.channels);

                                    stack_push(bgm_stack, convbuffer);
                                    //fwrite(convbuffer, 2 * vi.channels, bout, file_out);

                                    
                                    

                                    // Tell libvorbis how many samples we actually consumed
                                    vorbis_synthesis_read(&vdsp, bout);
                                }
                            }
                        }
                        if (ogg_page_eos(&opg))
                            eos = 1;
                    }
                }
                if (!eos)
                {
                    buffer = ogg_sync_buffer(&osynch_s, 4096);
                    bytes = fread(buffer, 1, 4096, file);
                    ogg_sync_wrote(&osynch_s, bytes);
                    if (bytes == 0)
                        eos = 1;
                }
            }

            sound_info = SoundInfo_New(vi.rate, vi.channels, 16, bgm_stack, 2 * vi.channels);
            vorbis_block_clear(&vblck);
            vorbis_dsp_clear(&vdsp);
        }
        else
        {
            ERROR("Error: Corrupt header during playback initialization.\n");
        }

        ogg_stream_clear(&ostream_s);
        vorbis_comment_clear(&vc);
        vorbis_info_clear(&vi);
    }

    ogg_sync_clear(&osynch_s);
    stack_delete(bgm_stack);
    fclose(file);
    //fclose(file_out);

    DEBUG("Done.\n");
    return sound_info;

}
