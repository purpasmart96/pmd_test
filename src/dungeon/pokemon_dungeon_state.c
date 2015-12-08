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

#include "dungeon/pokemon_dungeon_state.h"


// Called when starting a new dungeon
void SetUpDefualtStatus()
{
    for (int i = 0; i < NUMBER_OF_TEAMMATES; i++)
    {
        teammates[i].attack_multiplier = 1;
        teammates[i].sp_attack_multiplier = 1;
        teammates[i].defense_multiplier = 1;
        teammates[i].sp_defense_multiplier = 1;
        teammates[i].speed_multiplier = 1;
        teammates[i].belly = 100;
        teammates[i].burned = false;
        teammates[i].confused = false;
        teammates[i].paralysis = false;
        teammates[i].posioned = false;
        teammates[i].sleeping = false;
    }
}

// Called when then player gets past the stairs
void SetStatusAfterStairs()
{
    for (int i = 0; i < NUMBER_OF_TEAMMATES; i++)
    {
        teammates[i].attack_multiplier = 1;
        teammates[i].sp_attack_multiplier = 1;
        teammates[i].defense_multiplier = 1;
        teammates[i].sp_defense_multiplier = 1;
        teammates[i].speed_multiplier = 1;
        teammates[i].burned = false;
        teammates[i].confused = false;
        teammates[i].paralysis = false;
        teammates[i].posioned = false;
        teammates[i].sleeping = false;
    }
}
