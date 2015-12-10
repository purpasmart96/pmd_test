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

#include "dungeon/dungeon_state.h"


// Called when starting a new dungeon
void SetUpDefualtStatus()
{
    for (int i = 0; i < NUMBER_OF_TEAMMATES; i++)
    {
        team_mates[i].attack_multiplier = 1;
        team_mates[i].sp_attack_multiplier = 1;
        team_mates[i].defense_multiplier = 1;
        team_mates[i].sp_defense_multiplier = 1;
        team_mates[i].speed_multiplier = 1;
        team_mates[i].belly = 100;
        team_mates[i].burned = false;
        team_mates[i].confused = false;
        team_mates[i].paralysis = false;
        team_mates[i].posioned = false;
        team_mates[i].sleeping = false;
    }
}

// Called when then player gets past the stairs
void SetStatusAfterStairs()
{
    for (int i = 0; i < NUMBER_OF_TEAMMATES; i++)
    {
        team_mates[i].attack_multiplier = 1;
        team_mates[i].sp_attack_multiplier = 1;
        team_mates[i].defense_multiplier = 1;
        team_mates[i].sp_defense_multiplier = 1;
        team_mates[i].speed_multiplier = 1;
        team_mates[i].burned = false;
        team_mates[i].confused = false;
        team_mates[i].paralysis = false;
        team_mates[i].posioned = false;
        team_mates[i].sleeping = false;
    }
}
