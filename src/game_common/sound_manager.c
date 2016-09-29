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

#include "util.h"
#include "game_common/sound_manager.h"

typedef enum BgmSong
{
    BgmNone  = 0,
    BgmFortuneRavine = 1,

} BgmSong;

void SOUND_FadeOutBgm(s64 seconds)
{

}

void SOUND_WaitBgm()
{

}

void PlayBgmFortuneRavine(SoundCore *self, float vol)
{
}

static const struct BgmTable
{
    BgmSong bgm;
    const char *file_name;
    void(*Play)(SoundCore *, float);
    void(*Stop)(SoundCore *);
    void(*Loop)(SoundCore *);
    void(*FadeOut)(SoundCore *, s64);
    void(*Reserved1)();
    void(*Reserved2)();

} bgm_table[] =
{
    {
        BgmFortuneRavine,
        "data/sound/bgm/Fortune Ravine.ogg",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

void PlayBgm(SoundCore *self, float vol, BgmSong song)
{
    for (int i = 0; i < ARRAY_SIZE(bgm_table); i++)
    {
        if (bgm_table[i].bgm == song)
        {
            bgm_table[i].Play(self, vol);
        }
    }
}

static struct SfxTable
{
    const char *name;
    void(*Play)(SoundCore *, float);
    void(*Stop)(SoundCore *);
    void(*Reserved0)();
    void(*Reserved1)();
    void(*Reserved2)();

} sfx_table[] =
{
    {
        "None",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};
