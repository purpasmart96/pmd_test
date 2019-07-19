// Copyright(c) 2016 Purpasmart
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

#include "common/vec.h"

#include "game_common/item.h"
#include "game_common/move.h"
#include "game_common/dungeon.h"
#include "game_common/pokemon.h"

static Ability ability_table[] =
{
    { NoAbility,   "",              ""                                                   },
    { Stench,      "Stench",        "The stench may cause the target to flinch."         },
    { Drizzle,     "Drizzle",       "The Pok�mon makes it rain if it appears in battle." },
    { SpeedBoost,  "Speed Boost",   "The Pok�mon�s Speed stat is gradually boosted."     },
    { BattleArmor, "Battle Armor",  "The Pok�mon is protected against critical hits."    },
    { Sturdy,      "Sturdy",        "The Pok�mon is protected against 1-hit KO attacks." },
    { Damp,        "Damp",          "Prevents combatants from self destructing."         },
    { Limber,      "Limber",        "The Pok�mon is protected from paralysis."           },
    { SandVeil,    "Sand Veil",     "Boosts the Pok�mon�s evasion in a sandstorm."       },
    { Static,      "Static",        "Contact with the Pok�mon may cause paralysis."      },

};

Pokemon_t *Pokemon_New(const char *name, Species species, Type primary_type, Type sub_type, AbilityTypes ability, Sex sex, int level, int max_hp)
{
    Pokemon_t *pokemon = (Pokemon_t*) calloc(1, sizeof(*pokemon));

    SetPokemonName(pokemon, name);
    pokemon->species = species;
    pokemon->primary_type = primary_type;
    pokemon->sub_type = sub_type;
    SetPokemonAbility(pokemon, ability);
    pokemon->sex = sex;
    pokemon->level = level;
    pokemon->position = make_ivec2(0, 0);

    return pokemon;
}

PokemonParty *PokemonParty_New(int capacity)
{
    PokemonParty *party = (PokemonParty*) calloc(1, sizeof(*party));
    party->capacity = capacity;
    party->members = (Pokemon_t**) malloc(party->capacity * sizeof(*party->members));
    party->size = 0;

    for (int i = 0; i < party->capacity; i++)
    {
        party->members[i] = (Pokemon_t*) malloc(sizeof(*party->members[i]));
    }

    return party;
}

void AddPartyMember(PokemonParty *party, Pokemon_t *member)
{
    party->members[party->size++] = member;
}

Ability GetAbilityFromTable(AbilityTypes ability_name)
{
    //for (int i = 0; i < ARRAY_SIZE(ability_table); i++)
    return ability_table[ability_name];
}

void SetPokemonAbility(Pokemon_t *pokemon, AbilityTypes ability_name)
{
    //memcpy(&pokemon->ability, &ability_table[ability_name], sizeof(Ability)); ///GetAbilityFromTable(ability_name);
    pokemon->ability.ability_enum = ability_name;
    pokemon->ability.name = ability_table[ability_name].name;
    pokemon->ability.description = ability_table[ability_name].description;

}

AbilityTypes GetPokemonAbility(Pokemon_t *team_member)
{
    return team_member->ability.ability_enum;
}

void SetPokemonName(Pokemon_t *pokemon, const char *name)
{
    strlcpy(pokemon->name, name, sizeof(pokemon->name));
}

char *GetPokemonName(Pokemon_t *pokemon)
{
    printf("%s\n", pokemon->name);
    return pokemon->name;
}

Pokemon_t *GetCurrentLeader()
{
    //return &team_mates[CURRENT_LEADER];
}



