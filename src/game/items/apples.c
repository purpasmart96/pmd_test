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
#include "game/items/apples.h"

void AppleUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "Apple");
    AdjustBellySize(user, APPLE_HUNGER_REDUCE);
}

void AppleThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("AppleThrow stub called!\n");
}

void AppleDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("AppleDrop stub called!\n");
}

void BigAppleUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    RemoveItem(bag, user, location, "BigApple");
    AdjustBellySize(user, BIG_APPLE_HUNGER_REDUCE);
}

void BigAppleThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("BigAppleThrow stub called!\n");
}

void BigAppleDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location)
{
    printf("BigAppleDrop stub called!\n");
}
