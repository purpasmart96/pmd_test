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

#ifndef _APPLES_H_
#define _APPLES_H_

typedef struct PokemonParty PokemonParty;
typedef Pokemon_t Pokemon_t;

void AppleUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void AppleThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void AppleDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void BigAppleUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void BigAppleThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void BigAppleDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

#endif