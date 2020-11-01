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

#include "game/item.h"
#include "game/hunger.h"
#include "game/health.h"
#include "game/pokemon.h"

#include "game/items/berries.h"

void BerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item)
{
    switch (item)
    {
        case OranBerry:
            OranBerryUse(bag, party, user, location);
            break;
        case SitrusBerry:
            SitrusBerryUse(bag, party, user, location);
            break;
        case RawstBerry:
            break;
        case PechaBerry:
            break;
        case CheriBerry:
            break;
        case ChestoBerry:
            break;
        case OrenBerry:
            break;
        default:
            DEBUG("Item %d is not a berry!\n", item);
            break;
    }
}

void BerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item)
{
    switch (item)
    {
        case OranBerry:
            OranBerryThrow(bag, party, user, location);
            break;
        case SitrusBerry:
            SitrusBerryThrow(bag, party, user, location);
            break;
        case RawstBerry:
            break;
        case PechaBerry:
            break;
        case CheriBerry:
            break;
        case ChestoBerry:
            break;
        case OrenBerry:
            break;
        default:
            DEBUG("Item %d is not a berry!\n", item);
            break;
    }
}

void BerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item) 
{
    switch (item)
    {
        case OranBerry:
            OranBerryDrop(bag, party, user, location);
            break;
        case SitrusBerry:
            SitrusBerryDrop(bag, party, user, location);
            break;
        case RawstBerry:
            break;
        case PechaBerry:
            break;
        case CheriBerry:
            break;
        case ChestoBerry:
            break;
        case OrenBerry:
            break;
        default:
            DEBUG("Item %d is not a berry!\n", item);
            break;
    }
}

void OranBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    if (RemoveItem(bag, user, location, "OranBerry"))
    {
        AddHealth(user, ORAN_BERRY_HEALTH_HEAL);
        AdjustBellySize(user, BERRY_HUNGER_REDUCE);
    }
}

void OranBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "OranBerry");
    printf("OranBerryThrow stub called!\n");
}

void OranBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("OranBerryDrop stub called!\n");
}

void SitrusBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "SitrusBerry");
    AddHealth(user, ORAN_BERRY_HEALTH_HEAL);
    AdjustBellySize(user, BERRY_HUNGER_REDUCE);
}

void SitrusBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("SitrusBerryThrow stub called!\n");
}

void SitrusBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("SitrusBerryDrop stub called!\n");
}

void RawstBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "RawstBerry");

    AdjustBellySize(user, BERRY_HUNGER_REDUCE);
}

void RawstBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("RawstBerryThrow stub called!\n");
}

void RawstBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("RawstBerryDrop stub called!\n");
}

void CheriBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "CheriBerry");

    AdjustBellySize(user, BERRY_HUNGER_REDUCE);

}

void CheriBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("CheriBerryThrow stub called!\n");
}

void CheriBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("CheriBerryDrop stub called!\n");
}

void PechaBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "PechaBerry");

    AdjustBellySize(user, BERRY_HUNGER_REDUCE);
}

void PechaBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("PechaBerryThrow stub called!\n");
}

void PechaBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "PechaBerry");

}

void ChestoBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "ChestoBerry");

    AdjustBellySize(user, BERRY_HUNGER_REDUCE);

}

void ChestoBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("ChestoBerryThrow stub called!\n");
}

void ChestoBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("ChestoBerryDrop stub called!\n");
}
