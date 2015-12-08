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


#include "util.h"
#include "screen/screen.h"
#include "game_common/item_manager.h"
#include "dungeon/pokemon_dungeon_state.h"
#include "dungeon/dungeon_gen.h"

int main()
{

    ClearBag();
    GiveItemToTeamMember(&players_team[CURRENT_LEADER], ReviverSeed);
    printf("Item on player is %s\n", GetItemNameFromId(players_team[CURRENT_LEADER].held_item));
    RemoveItemFromTeamMember(&players_team[CURRENT_LEADER], ReviverSeed);
    printf("Item on player now is %s\n", GetItemNameFromId(players_team[CURRENT_LEADER].held_item));
    printf("Item in Bag slot 0 = %s\n", GetItemNameFromId(bag.items[0]));
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(OranBerry);
    AddItemToBag(OranBerry);
    AddItemToBag(JoySeed);
    AddItemToBag(JoySeed);
    AddItemToBag(ReviverSeed);
    AddItemToBag(ReviverSeed);

    GiveItemToTeamMember(&players_team[CURRENT_LEADER], PowerBand);
    RemoveItemFromTeamMember(&players_team[CURRENT_LEADER], PowerBand);
    RemoveItemFromBag(PowerBand);
    RemoveItemFromBag(ReviverSeed);
    SetUpDefualtStatus();
    printf("Leaders belly is %d\n", teammates[CURRENT_LEADER].belly);
    //dungeon_main();
    screen_Init();
    printf("This is only the beginning!\n");
    printf("Press Any Key to Continue\n");
    _getch();
    screen_Free();
    return 0;
}