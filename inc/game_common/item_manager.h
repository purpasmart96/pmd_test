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


#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

#include "pokemon/database.h"

#define NO_ITEMS 0
#define MAX_ITEMS 48
#define NEXT_SLOT i + 1

typedef struct {
    Items items[MAX_ITEMS]; // The amount of items that can be in the bag
    int size; // Current amount of items in the bag
}TempBag;

typedef struct
{
    Items items[MAX_ITEMS]; // The amount of items that can be in the bag
    int size; // Current amount of items in the bag
}Bag;

TempBag temp_bag;
Bag bag;

void ClearBag();
bool IsBagEmpty();
bool IsBagFull();
void DisplayBag();
void AddEmptySlots();
void UpdateBag();
void PushItemToTop(Items the_item);
void GiveItemToTeamMember(Pokemon *team_member, Items the_item);
void AddItemToBag(Items the_item);
void RemoveItemFromBag(Items the_item);
void RemoveItemFromTeamMember(Pokemon *team_member, Items the_item);
void UseItemFromBag(Pokemon *team_member, Items the_item);
char *GetItemNameFromId(Items the_item);

#endif
