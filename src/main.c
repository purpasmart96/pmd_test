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
#include "dungeon/dungeon_state.h"
#include "dungeon/dungeon_gen.h"
#include "screen/load_png.h"
#include "audio/audio.h"

int main()
{
    ClearBag();
    printf("Press Esc in the other window to Continue!\n");
    screen_Init();
    GiveItemToTeamMember(&team_mates[CURRENT_LEADER], ReviverSeed);
    printf("Item on player is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
    RemoveItemFromTeamMember(&team_mates[CURRENT_LEADER], ReviverSeed);
    printf("Item on player now is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
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

    GiveItemToTeamMember(&team_mates[CURRENT_LEADER], PowerBand);
    RemoveItemFromTeamMember(&team_mates[CURRENT_LEADER], PowerBand);
    RemoveItemFromBag(PowerBand);
    RemoveItemFromBag(ReviverSeed);
    RemoveItemFromBag(ReviverSeed);
    RemoveItemFromBag(OranBerry);
    RemoveItemFromBag(OranBerry);
    RemoveItemFromBag(OranBerry);
    RemoveItemFromBag(OranBerry);
    SetUpDefualtStatus();
    AddItemToBag(Apple);
    UseItemFromBag(&team_mates[CURRENT_LEADER], Apple);
    AddItemToBag(Apple);
    AddItemToBag(Apple);
    AddItemToBag(Apple);
    AddItemToBag(Apple);
    AddItemToBag(Apple);
    RemoveItemFromBag(JoySeed);
    RemoveItemFromBag(JoySeed);
    printf("Leaders belly is %d\n", team_mates[CURRENT_LEADER].status.belly);
    DisplayBag();
    SOUND_Main();
    dungeon_main();
    dungeon_free();

    //LoadPngFile("test.png");
    screen_Free();
    printf("This is only the beginning!\n");
    printf("Press Any Key to Continue\n");
    _getch();
    return 0;
}