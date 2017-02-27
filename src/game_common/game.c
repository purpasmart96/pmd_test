// Copyright(c) 2016 Purpasmart
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
#include <GLFW/glfw3.h>

#include "common/vec.h"
#include "common/list_generic.h"
#include "common/rand_num.h"

#include "game_common/pokemon.h"
#include "game_common/display.h"
#include "game_common/input.h"
#include "game_common/item.h"
#include "game_common/game.h"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Game_t *game = glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //glfwGetKeyName(key, scancode);
        //printf("You pressed %s\n", );
        printf("You pressed E\n");

        //dungeon_main();
        //screen_Init();
        //struct Bag *PlayerBag = NULL; //calloc(1, sizeof(&PlayerBag));//CreateBag(MAX_ITEMS);
        //ClearBag(&PlayerBag);
        //printf("Press Esc in the other window to Continue!\n");
        //GiveItemToTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
        //printf("Item on player is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
        //RemoveItemFromTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
        //printf("Item on player now is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));

        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "OranBerry");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "JoySeed");
        AddItemToBag_(game->bag, "ReviverSeed");
        AddItemToBag_(game->bag, "ReviverSeed");

        //GiveItemToTeamMember(game->bag, &team_mates[CURRENT_LEADER], PowerBand);
        //RemoveItemFromTeamMemberToBag(game->bag, &team_mates[CURRENT_LEADER], PowerBand);
        //RemoveItemFromBag_(game->bag, "PowerBand");
        RemoveItemFromBag_(game->bag, "ReviverSeed");
        RemoveItemFromBag_(game->bag, "ReviverSeed");
        RemoveItemFromBag_(game->bag, "OranBerry");
        RemoveItemFromBag_(game->bag, "OranBerry");
        RemoveItemFromBag_(game->bag, "OranBerry");
        RemoveItemFromBag_(game->bag, "OranBerry");
        printf("Current bag size is %d\n", game->bag->size);
        //SetUpDefualtStatus();
        AddItemToBag_(game->bag, "Apple");
        //UseItemFromBag(game->bag, &team_mates[CURRENT_LEADER], Apple);
        AddItemToBag_(game->bag, "Apple");
        AddItemToBag_(game->bag, "Apple");
        AddItemToBag_(game->bag, "Apple");
        AddItemToBag_(game->bag, "Apple");
        AddItemToBag_(game->bag, "Apple");
        RemoveItemFromBag_(game->bag, "JoySeed");
        RemoveItemFromBag_(game->bag, "JoySeed");
        printf("Current bag size is %d\n", game->bag->size);
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


        DisplayBag(game->bag);
    }
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		printf("Removing Apple\n");
		RemoveItemFromBag_(game->bag, "Apple");
		DisplayBag(game->bag);
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		printf("Removing JoySeed\n");
		RemoveItemFromBag_(game->bag, "JoySeed");
		DisplayBag(game->bag);
	}

}

Game_t *Game_New(bool init)
{
    Game_t *game = malloc(sizeof(*game));

    if (!game)
    {
        return NULL;
    }
    else if (init)
    {
        Game_Init(game);
    }

    return game;
}

void Game_Init(Game_t *self)
{
    self->running = true;
    self->screen  = Screen_New(true);
    self->input   = Input_New(true);
    self->bag     = Bag_New(true);
    //self->party   = PokemonParty_New(4);

    //Pokemon *leader = Pokemon_New("TestName", Bulbasaur, Grass, Poison, Overgrow, Female, 5, 20);

    //AddPartyMember(self->party, leader);

    glfwSetWindowUserPointer(self->screen->window, self);
    glfwSetKeyCallback(self->screen->window, key_callback);
}

void Game_Update(Game_t *self)
{
    Screen_Update(self->screen);
    Input_Update(self->input);

    if (glfwWindowShouldClose(self->screen->window))
    {
        self->running = false;
    }

}

void Game_ShutDown(Game_t *self)
{
    Bag_ShutDown(self->bag);
    Input_ShutDown(self->input);
    Screen_Shutdown(self->screen);

    free(self);
}
