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

#include "util.h"
#include "game/pokemon.h"
#include "game/health.h"


void AddHealth(Pokemon_t *team_member, int amount)
{
    if (team_member->current_hp == team_member->max_hp)
    {
        DEBUG("%s's HP is already Full!\n", team_member->name);
    }
    else
    {
        DEBUG("%s Gained %d HP!\n", team_member->name, amount);
        team_member->current_hp += amount;

        team_member->current_hp = MIN(team_member->current_hp, team_member->max_hp);
        //CLAMP(team_member->current_hp, HP_MIN, team_member->max_hp);
        DEBUG("%s's current HP is %d HP!\n", team_member->name, team_member->current_hp);
    }
}

void DecreaseHealth(Pokemon_t *defender, int amount)
{
    if (defender->current_hp != HP_ZERO)
    {
        defender->current_hp -= amount;
        DEBUG("%s Took %d Damage!\n", defender->name, amount);
    }
    else
    {
        return;
    }

    if (defender->current_hp < HP_MIN)
    {
        defender->current_hp = HP_ZERO;
        DEBUG("%s Fainted!\n", defender->name);
    }

}

void SetStatusAttribute(Pokemon_t *defender, int amount)
{

}

