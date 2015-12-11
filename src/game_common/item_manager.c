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
#include "game_common/hunger_manager.h"

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

void AddEmptySlots()
{
    for (int i = bag.size; i < MAX_ITEMS; i++)
    {
        bag.items[i] = None;
    }

}

void PushItemToTop(Items the_item)
{
    bag.items[bag.size] = the_item;
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
                bag.size--;
                PushItemToTop(bag.items[i]);
                bag.items[i] = bag.items[i + 1];
                AddEmptySlots();
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

void UseItemFromBag(Pokemon *team_member, Items the_item)
{
    switch (the_item)
    {
    case 0:
    {

    }
    case Apple:
    {
        AdjustBellySize(team_member, APPLE_HUNGER_REDUCE);
        RemoveItemFromBag(Apple);
        break;
    }
    
    default:
        break;
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
    case Stick:
    {
        break;
    }
    case IronThorn:
    {
        break;
    }
    case SilverSpike:
    {
        break;
    }
    case GoldFang:
    {
        break;
    }
    case CacneaSpike:
    {
        break;
    }
    case CorsolaTwig:
    {
        break;
    }
    case Gravelerock:
    {
        break;
    }
    case GeoPebble:
    {
        break;
    }
    case GoldThorn:
    {
        item_name = "GoldThorn";
        break;
    }
    case RareFossil:
    {
        break;
    }
    case NoSlipCap:
    {
        break;
    }
    case YRaySpecs:
    {
        item_name = "YRaySpecs";
        break;
    }
    case GaggleSpecs:
    {
        break;
    }
    case MobileScarf:
    {
        break;
    }
    case HealRibbon:
    {
        break;
    }
    case TwistBand:
    {
        break;
    }
    case ScopeLens:
    {
        break;
    }
    case PatsyBand:
    {
        break;
    }
    case NoStickCap:
    {
        break;
    }
    case PierceBand:
    {
        break;
    }
    case JoyRibbon:
    {
        item_name = "JoyRibbon";
        break;
    }
    case XRaySpecs:
    {
        break;
    }
    case PersimBand:
    {
        break;
    }
    case PowerBand:
    {
        item_name = "PowerBand";
        break;
    }
    case 25:
    {
        item_name = "PechaScarf";
        break;
    }
    case OranBerry:
    {
        item_name = "OranBerry";
        break;
    }
    case ReviverSeed:
    {
        item_name = "ReviverSeed";
        break;
    }
    case JoySeed:
    {
        item_name = "JoySeed";
        break;
    }

    default:
        break;
    }

    return item_name;
}
