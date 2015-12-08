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

#include "game_common/item_manager.h"

void ClearBag()
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        bag.items[i] = None;
        bag.size = NO_ITEMS;
    }
}

void GiveItemToTeamMember(Pokemon *team_member, Items the_item)
{
    team_member->held_item = the_item;
}

bool IsBagEmpty()
{
    if (bag.size == NO_ITEMS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsBagFull()
{
    if (bag.size == MAX_ITEMS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AddItemToBag(Items the_item)
{
    if (IsBagFull() == false)
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (bag.items[i] != None)
            {
                continue; // skip to the next slot in the bag
            }
            else
            {
                bag.items[i] = the_item;
                bag.size++;
                return;
            }
        }
    }
    else
    {
        printf("Bag is currently full!\n");
        printf("Can't add %s to the bag\n", GetItemNameFromId(the_item));
        return;
    }
}

void RemoveItemFromBag(Items the_item)
{
    if (IsBagEmpty() == false)
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (bag.items[i] != the_item)
            {
                continue; // skip to the next slot in the bag
            }
            else
            {
                bag.items[i] = None;
                bag.size--;
                return;
            }
        }
    }
    else
    {
        printf("Bag is empty!\n");
        return;
    }
}

// Removes the item from the team member and puts it in the bag
void RemoveItemFromTeamMember(Pokemon *team_member, Items the_item)
{
    team_member->held_item = None;
    AddItemToBag(the_item);
}

char *GetItemNameFromId(Items the_item)
{
    char *item_name = NULL;
    switch (the_item)
    {
    case 0:
    {
        item_name = "None";
        break;
    }
    case 1:
    {
        break;
    }
    case 2:
    {
        break;
    }
    case 3:
    {
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        break;
    }
    case 7:
    {
        break;
    }
    case 8:
    {
        break;
    }
    case 9:
    {
        item_name = "GoldThorn";
        break;
    }
    case 10:
    {
        break;
    }
    case 11:
    {
        break;
    }
    case 12:
    {
        break;
    }
    case 70:
    {
        item_name = "OranBerry";
        break;
    }
    case 73:
    {
        item_name = "ReviverSeed";
        break;
    }
    case 89:
    {
        item_name = "JoySeed";
        break;
    }

    default:
        break;
    }

    return item_name;
}
