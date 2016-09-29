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

#include "game_common/item_manager.h"
#include "game_common/move_manager.h"
#include "game_common/dungeon_manager.h"
#include "game_common/pokemon_manager.h"

static const Ability ability_table[] =
{
    { NoAbility, "", "" },
    { Stench, "Stench", "The stench may cause the target to flinch." },
    { Drizzle, "Drizzle", "The Pokémon makes it rain if it appears in battle." },
    { SpeedBoost, "Speed Boost", "The Pokémon’s Speed stat is gradually boosted." },
    { BattleArmor, "Battle Armor", "The Pokémon is protected against critical hits." },
    { Sturdy, "Sturdy", "The Pokémon is protected against 1-hit KO attacks." },
    { Damp, "Damp", "Prevents combatants from self destructing." },
    { Limber, "Limber", "The Pokémon is protected from paralysis." },
    { SandVeil, "Sand Veil", "Boosts the Pokémon’s evasion in a sandstorm." },
    { Static, "Static", "Contact with the Pokémon may cause paralysis." },

};

Pokemon *CreatePokemon(const char *name, Species species, Type primary_type, Type sub_type, Ability ability, Sex sex, int level, int max_hp)
{
    Pokemon *pokemon = malloc(sizeof(*pokemon));

    SetPokemonName(pokemon, name);
    pokemon->species = species;
    pokemon->primary_type = primary_type;
    pokemon->sub_type = sub_type;
    pokemon->ability = ability;
    pokemon->sex = sex;
    pokemon->level = level;

    return pokemon;
}

struct PokemonParty *CreateParty(int capacity, Pokemon *leader)
{
    PokemonParty *party = malloc(sizeof(*party));
    party->capacity = capacity;
    party->members = (Pokemon**)malloc(sizeof(Pokemon) * party->capacity);
    party->size = 0;
    AddPartyMember(party, leader);
}

void AddPartyMember(PokemonParty *party, Pokemon *member)
{
    party->members[party->size++] = member;
}

Ability GetAbilityFromTable(AbilityTypes ability_name)
{
    //for (int i = 0; i < ARRAY_SIZE(ability_table); i++)
    return ability_table[ability_name];
}

void SetPokemonAbility(Pokemon *pokemon, AbilityTypes ability_name)
{
    Ability ability = GetAbilityFromTable(ability_name);
    pokemon->ability = ability;
}

AbilityTypes GetPokemonAbility(Pokemon *team_member)
{
    return team_member->ability.ability_enum;
}

void SetPokemonName(Pokemon *team_member, const char *name)
{
    strlcpy(team_member->name, name, strlen(name));
}

char *GetPokemonName(Pokemon *pokemon)
{
    printf("%s\n", pokemon->name);
    return pokemon->name;
}

Pokemon *GetCurrentLeader()
{
    //return &team_mates[CURRENT_LEADER];
}



