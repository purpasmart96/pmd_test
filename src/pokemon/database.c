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

#include "pokemon/database.h"


static Ability ability_table[] =
{
    { Stench,      "Stench",       "The stench may cause the target to flinch."           },
    { Drizzle,     "Drizzle",      "The Pokémon makes it rain if it appears in battle."   },
    { SpeedBoost,  "Speed Boost",  "The Pokémon’s Speed stat is gradually boosted."       },
    { BattleArmor, "Battle Armor", "The Pokémon is protected against critical hits."      },
    { Sturdy,      "Sturdy",       "The Pokémon is protected against 1-hit KO attacks."   },
    { Damp,        "Damp",         "Prevents combatants from self destructing."           },
    { Limber,      "Limber",       "The Pokémon is protected from paralysis."             },
    { SandVeil,    "Sand Veil",    "Boosts the Pokémon’s evasion in a sandstorm."         },
    { Static,      "Static",       "Contact with the Pokémon may cause paralysis."        },

};


int GetPokeDexNumFromPoke()
{

}

void SetPokemonAbility(Pokemon *team_member, AbilityNameEnum ability)
{
    team_member->ability.ability_enum = ability;
    team_member->ability = ability_table[team_member->ability.ability_enum];
}

void GetPokemonAbility(Pokemon *team_member)
{

}

void SetPokemonName(Pokemon *team_member, char *name)
{
    team_member->name = name;
}

void GetPokemonName(Pokemon *team_member)
{
    printf("%s\n", team_member->name);
}