// Copyright(c) 2015 Purpasmart
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

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "audio_core/sound_core.h"

#include <pthread.h>

#define FPS_LIMIT_MS 1.0 / 60.0 * 1000.0
#define FPS_LIMIT 1.0 / 12.0
//#define FPS_LIMIT 1.0 / 60.0
#define FPS_LIMIT_FAST 1.0 / 20.0
#define PLAYER_MOVEMENT_SPEED 1.0 / 20.0

#define USE_BATCH_RENDERER 
//#define USE_SLOW_RENDERER
//#define USE_FAST_OLD_RENDERER

#define	MAX_CVAR_VALUE_STRING	256


// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
typedef struct
{
    int	  handle;
    int	  modification_count;
    float value;
    int   integer;
    char  string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

typedef struct Cvar
{
    char *name;
    char *string;
    char *reset_string;		  // cvar_restart will reset to this value
    char *latched_string;     // for CVAR_LATCH vars
    int  flags;
    bool modified;            // set each time the cvar is changed
    int  modification_count;  // incremented each time the cvar is changed
    float value;              // atof(string)
    int	integer;              // atoi(string)
    struct Cvar *next;
    struct Cvar *hash_next;
} Cvar;

typedef enum
{
    GAME_PUASED,
    GAME_ACTIVE,
} GameSate_t;

typedef struct Game_s
{
    bool running;
    struct Player_s *player;
    struct Screen_s *screen;
    struct Bag *bag;
    struct PokemonParty *party;
    ALState *audio_state;
    struct TimeInfo_s *time_info;
    double accumulator;
    double alpha;
    double current_time;
    double previous_time;
    double timer;
    //double delta_time;
    u64 frames;
    u64 updates;
} Game_t;


Game_t *Game_New(bool init);
void Game_Init(Game_t *self);
void Game_ShutDown(Game_t *self);
void Game_Update(Game_t *self);

#endif
