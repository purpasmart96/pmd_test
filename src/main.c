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


#include "util.h"
#include "screen/screen.h"
#include "game_common/item_manager.h"
#include "game_common/move_manager.h"
#include "game_common/game_manager.h"
#include "game_common/dungeon_manager.h"
#include "common/list_generic.h"
#include "dungeon/dungeon_gen.h"

static struct Bag PlayerBag;

int main(int argc, char **argv)
{
    //dungeon_main();
    //screen_Init();
    //struct Bag *PlayerBag = NULL; //calloc(1, sizeof(&PlayerBag));//CreateBag(MAX_ITEMS);
    ClearBag(&PlayerBag);
    //printf("Press Esc in the other window to Continue!\n");
    //GiveItemToTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
    //printf("Item on player is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
    //RemoveItemFromTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
    //printf("Item on player now is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "OranBerry");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "JoySeed");
    AddItemToBag_(&PlayerBag, "ReviverSeed");
    AddItemToBag_(&PlayerBag, "ReviverSeed");

    //GiveItemToTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], PowerBand);
    //RemoveItemFromTeamMemberToBag(&PlayerBag, &team_mates[CURRENT_LEADER], PowerBand);
    //RemoveItemFromBag_(&PlayerBag, "PowerBand");
    RemoveItemFromBag_(&PlayerBag, "ReviverSeed");
    RemoveItemFromBag_(&PlayerBag, "ReviverSeed");
    RemoveItemFromBag_(&PlayerBag, "OranBerry");
    RemoveItemFromBag_(&PlayerBag, "OranBerry");
    RemoveItemFromBag_(&PlayerBag, "OranBerry");
    RemoveItemFromBag_(&PlayerBag, "OranBerry");
    //SetUpDefualtStatus();
    AddItemToBag_(&PlayerBag, "Apple");
    //UseItemFromBag(&PlayerBag, &team_mates[CURRENT_LEADER], Apple);
    AddItemToBag_(&PlayerBag, "Apple");
    AddItemToBag_(&PlayerBag, "Apple");
    AddItemToBag_(&PlayerBag, "Apple");
    AddItemToBag_(&PlayerBag, "Apple");
    AddItemToBag_(&PlayerBag, "Apple");
    RemoveItemFromBag_(&PlayerBag, "JoySeed");
    RemoveItemFromBag_(&PlayerBag, "JoySeed");
    //UseItemFromBag(&PlayerBag, &team_mates[CURRENT_LEADER], "OranBerry");
    //printf("Leaders belly is %d\n", team_mates[CURRENT_LEADER].status.current_belly);
    //memset(&enemies, 0, sizeof(enemies));
    //enemies[0].name = "TestPoke";
    //enemies[0].defense = 44;
    //enemies[0].max_hp = 100;
    //enemies[0].current_hp = 100;
    //SetPokemonName(GetCurrentLeader(), "TestName");
    //team_mates[CURRENT_LEADER].GetPokemonName = GetPokemonName;
    //team_mates[CURRENT_LEADER].GetPokemonName(&team_mates[CURRENT_LEADER]);
    //CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);
    //CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);
    ///CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);
    //CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);
    //CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);
    //CalculateDamage(KarateChop, &team_mates[CURRENT_LEADER], &enemies[0]);


    DisplayBag(&PlayerBag);
    //SOUND_Main();
    //dungeon_main();

    //Game *game = Game_New(true);

    //while (game->running)
    //{
    //    Game_Update(game);
    //    ListChar *list_test = LIST_NEW(ListChar);
    //    char val = 'A';
    //    LIST_PUSH(ListChar, list_test, val);
    //}
    //Game_ShutDown(game);

    // Linked list mem test
    ListChar *list_test = LIST_NEW(ListChar);
    char val0 = 'A';
    char val1 = 'B';
    char val2 = 'C';
    char val3 = 'D';
    for (int i = 0; i < 1000000; i++)
    {
        LIST_PUSH(ListChar, list_test, val0);
        LIST_PUSH(ListChar, list_test, val1);
        LIST_PUSH(ListChar, list_test, val2);
        LIST_PUSH(ListChar, list_test, val3);
    }
    LIST_DELETE(ListChar, list_test);

    //printf("This is only the beginning!\n");
    //printf("Press Any Key to Continue\n");
    //_getch();
    //dungeon_free();
    return 0;
}