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

//static Ability ability_table[] =
//{
//    { NoAbility,   "",              ""                                                   },
//    { Stench,      "Stench",        "The stench may cause the target to flinch."         },
//    { Drizzle,     "Drizzle",       "The Pokémon makes it rain if it appears in battle." },
//    { SpeedBoost,  "Speed Boost",   "The Pokémon’s Speed stat is gradually boosted."     },
//    { BattleArmor, "Battle Armor",  "The Pokémon is protected against critical hits."    },
//    { Sturdy,      "Sturdy",        "The Pokémon is protected against 1-hit KO attacks." },
//    { Damp,        "Damp",          "Prevents combatants from self destructing."         },
//    { Limber,      "Limber",        "The Pokémon is protected from paralysis."           },
//    { SandVeil,    "Sand Veil",     "Boosts the Pokémon’s evasion in a sandstorm."       },
//    { Static,      "Static",        "Contact with the Pokémon may cause paralysis."      },
//};

static void PokemonStatusInit(Pokemon_t *pokemon)
{
    pokemon->status = malloc(sizeof(*pokemon->status));
    pokemon->status->attack_multiplier = 1;
    pokemon->status->sp_attack_multiplier = 1;
    pokemon->status->defense_multiplier = 1;
    pokemon->status->sp_defense_multiplier = 1;
    pokemon->status->speed_multiplier = 1;
    pokemon->status->current_belly = 100;
    pokemon->status->max_belly = 100;
    pokemon->status->burned = false;
    pokemon->status->confused = false;
    pokemon->status->paralysis = false;
    pokemon->status->posioned = false;
    pokemon->status->sleeping = false;
}

void Pokemon_StatusReset(Pokemon_t *pokemon, bool first_floor)
{
    if (first_floor)
    {
        pokemon->status->current_belly = 100;
        pokemon->status->max_belly = 100;
    }

    pokemon->status->attack_multiplier = 1;
    pokemon->status->sp_attack_multiplier = 1;
    pokemon->status->defense_multiplier = 1;
    pokemon->status->sp_defense_multiplier = 1;
    pokemon->status->speed_multiplier = 1;
    pokemon->status->burned = false;
    pokemon->status->confused = false;
    pokemon->status->paralysis = false;
    pokemon->status->posioned = false;
    pokemon->status->sleeping = false;
}

Pokemon_t *Pokemon_New(const char *name, Species species, Type primary_type, Type sub_type, AbilityTypes ability, Sex sex, int level, int max_hp, bool team_leader)
{
    Pokemon_t *pokemon = calloc(1, sizeof(*pokemon));

    SetPokemonName(pokemon, name);
    pokemon->species = species;
    pokemon->primary_type = primary_type;
    pokemon->sub_type = sub_type;
    SetPokemonAbility(pokemon, ability);
    pokemon->sex = sex;
    pokemon->level = level;
    pokemon->max_hp = 255;
    PokemonStatusInit(pokemon);
    pokemon->team_leader = team_leader;

    if (team_leader)
    {
        pokemon->position = GetPlayerSpawnPoint(GetDungeonObject());
    }
    else 
    {
        pokemon->position = make_ivec2(0, 0);
    }

    return pokemon;
}

PokemonParty *PokemonParty_New(int capacity)
{
    PokemonParty *party = malloc(sizeof(*party));
    party->capacity = capacity;
    party->members = malloc(sizeof(Pokemon_t) * party->capacity);

    party->size = 0;

    return party;
}

void PokemonParty_Destroy(PokemonParty *party)
{
    free(party->members);
    free(party);
}

void AddPartyMember(PokemonParty *party, Pokemon_t *member)
{
    party->members[party->size++] = member;
}


void SetPokemonAbility(Pokemon_t *pokemon, AbilityTypes ability_name)
{
    //memcpy(&pokemon->ability, &ability_table[ability_name], sizeof(Ability)); ///GetAbilityFromTable(ability_name);
    pokemon->ability = ability_name;
    //pokemon->ability.name = ability_table[ability_name].name;
    //pokemon->ability.description = ability_table[ability_name].description;

}

AbilityTypes GetPokemonAbility(Pokemon_t *team_member)
{
    return team_member->ability;
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

Pokemon_t *GetCurrentLeader(PokemonParty *party)
{
    const int current_leader = 0;

    return party->members[current_leader];
}



