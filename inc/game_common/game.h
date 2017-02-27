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


typedef struct Game_s
{
    bool running;
    struct Input_s *input;
    struct Screen_s *screen;
    struct Bag *bag;
    struct PokemonParty *party;
    //struct ListInt *list;
} Game_t;


Game_t *Game_New(bool init);
void Game_Init(Game_t *self);
void Game_ShutDown(Game_t *self);
void Game_Update(Game_t *self);

#endif
