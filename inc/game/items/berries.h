// Copyright(c) 2016 <Purpasmart>
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

#ifndef _BERRIES_H_
#define _BERRIES_H_

typedef struct PokemonParty PokemonParty;
typedef struct Pokemon_s Pokemon_t;

void BerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item);
void BerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item);
void BerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location, Items item);

void OranBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void OranBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void OranBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void SitrusBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void SitrusBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void SitrusBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void RawstBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void RawstBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void RawstBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void CheriBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void CheriBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void CheriBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void PechaBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void PechaBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void PechaBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

void ChestoBerryUse(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void ChestoBerryThrow(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);
void ChestoBerryDrop(Bag *bag, PokemonParty *party, Pokemon_t *user, ItemLocation location);

#endif
