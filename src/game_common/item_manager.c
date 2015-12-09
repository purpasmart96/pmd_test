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
    if (!IsBagFull())
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (bag.items[i] == None) // Find a empty slot
            {
                bag.items[i] = the_item;
                bag.size++;
                return;
            }
            else
            {
                continue; // Skip to the next slot in the bag from the bottem
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
    if (!IsBagEmpty())
    {
        for (int i = MAX_ITEMS; i >= 0; i--)
        {
            if (bag.items[i] == the_item) // Find the slot that has the item were looking for
            {
                bag.items[i] = None;
                bag.size--;
                return;
            }
            else
            {
                continue; // Skip to the next slot in the bag from the top
            }
        }
    }
    else
    {
        printf("Bag is empty!\n");
        return;
    }
}

// Takes a item from the bag or ground and puts it on the desired team member
// If there is item already on it then swap it and put the current item
// that's on the team member back in the bag
void GiveItemToTeamMember(Pokemon *team_member, Items the_item)
{
    if (team_member->held_item == None)
    {
        printf("Gave the %s to the Team Member\n", GetItemNameFromId(the_item));
        team_member->held_item = the_item;
        return;
    }
    else
    {
        if (!IsBagFull())
        {
            printf("Put the %s in the bag\n", GetItemNameFromId(team_member->held_item));
            printf("Gave the %s to the Team Member\n", GetItemNameFromId(the_item));
            AddItemToBag(team_member->held_item);
            team_member->held_item = the_item;
            return;
        }
        else
        {
            // Do nothing
            printf("Cannot give Team Member a item!\n");
            return;
        }
    }

}

// Removes the item from the team member and puts it in the bag
void RemoveItemFromTeamMember(Pokemon *team_member, Items the_item)
{
    if (team_member->held_item != None)
    {
        if (!IsBagFull())
        {
            team_member->held_item = None;
            AddItemToBag(the_item);
            return;
        }
        else
        {
            // Do nothing
            printf("Cannot take item from Team Member!\n");
            return;
        }
    }
    else
    {
        printf("There is no item on it!\n");
        return;
    }
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
        item_name = "";
        break;
    }
    case 26:
    {
        item_name = "PowerBand";
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
