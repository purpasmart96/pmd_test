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

#include "game_common/item.h"
#include "game_common/hunger.h"
#include "game_common/dungeon.h"
#include "game_common/pokemon.h"

// Called when starting a new dungeon
void Dungeon_SetUpDefualtStatus(PokemonParty *party)
{
    for (int i = 0; i < party->size; i++)
    {
        party->members[i]->status->attack_multiplier = 1;
        party->members[i]->status->sp_attack_multiplier = 1;
        party->members[i]->status->defense_multiplier = 1;
        party->members[i]->status->sp_defense_multiplier = 1;
        party->members[i]->status->speed_multiplier = 1;
        party->members[i]->status->current_belly = DEFUALT_BELLY_SIZE;
        party->members[i]->status->max_belly = DEFUALT_BELLY_SIZE;
        party->members[i]->status->burned = false;
        party->members[i]->status->confused = false;
        party->members[i]->status->paralysis = false;
        party->members[i]->status->posioned = false;
        party->members[i]->status->sleeping = false;
    }
}

// Called when then player gets past the stairs
void Dungeon_SetStatusAfterStairs(PokemonParty *party)
{
    for (int i = 0; i < party->size; i++)
    {
        party->members[i]->status->attack_multiplier = 1;
        party->members[i]->status->sp_attack_multiplier = 1;
        party->members[i]->status->defense_multiplier = 1;
        party->members[i]->status->sp_defense_multiplier = 1;
        party->members[i]->status->speed_multiplier = 1;
        party->members[i]->status->burned = false;
        party->members[i]->status->confused = false;
        party->members[i]->status->paralysis = false;
        party->members[i]->status->posioned = false;
        party->members[i]->status->sleeping = false;
    }
}

void Dungeon_NextFloorLevel(DungeonState *self, PokemonParty *party)
{
    Dungeon_SetStatusAfterStairs(party);
    self->floor_level++;
    self->current_weather = WeatherClear;
}