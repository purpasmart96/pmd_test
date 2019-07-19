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

#include "audio_core/sound_core.h"

#include "game_common/dungeon.h"
#include "game_common/pokemon.h"
#include "game_common/display.h"
//#include "game_common/shader.h"
#include "game_common/sprites.h"
#include "game_common/input.h"
#include "game_common/player.h"
#include "game_common/item.h"
#include "game_common/game.h"


void cursor_enter_callback(GLFWwindow *window, int entered)
{
    if (entered)
    {
        // The cursor entered the client area of the window
    }
    else
    {
        // The cursor left the client area of the window
    }
}

static int prev_state = GLFW_RELEASE;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Game_t *game = glfwGetWindowUserPointer(window);

    //game->player->input->keys[key] = true;
    game->player->input->current_key = key;
    game->player->input->scan_code = scancode;
    game->player->input->action = action;
    game->player->input->mods = mods;

    Player_Update(game->player);

    

    //if (action == GLFW_PRESS)
    //{
     //game->input->keys[key] = action;
     //game->input->current_key = key;
    //}

     //if (key != 0 && action == GLFW_PRESS)
     //{
     //	game->input->keys[key] = action;
     //	game->input->current_key = key;
     //}


     //int new_state = action;
     //if (new_state == GLFW_RELEASE && prev_state == GLFW_PRESS)
     //{
     //	DEBUG("%s Key pressed\n", glfwGetKeyName(key, scancode));
     //}
     //prev_state = new_state;

     //int new_state = action;
     //if (action == GLFW_REPEAT || action == GLFW_PRESS)
     //{
     //	DEBUG("%s Key pressed\n", glfwGetKeyName(key, scancode));
     //}
     //prev_state = new_state;
    

    
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //glfwGetKeyName(key, scancode);
        //printf("You pressed %s\n", );
        //printf("You pressed E\n");
        //SoundInfo *si = ogg_decode("D:/PokeMysteryDun/pmd_fix/data/sound/bgm/Aegis Cave.ogg");
        //AL_State_LoadBuffer(game->audio_state);
        //while (true)
        //{
        //    alGetSourcei(game->audio_state->source, AL_SOURCE_STATE, &game->audio_state->source_state);
        //    if (game->audio_state->source_state != AL_PLAYING)
        //    {
        //        alSourcePlay(game->audio_state->source);
        //    }
        //}
        //DEBUG("Done playing \n");
    //}

     //dungeon_main();
     //screen_Init();
     //struct Bag *PlayerBag = NULL; //calloc(1, sizeof(&PlayerBag));//CreateBag(MAX_ITEMS);
     //ClearBag(&PlayerBag);
     //printf("Press Esc in the other window to Continue!\n");
     //GiveItemToTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
     //printf("Item on player is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));
     //RemoveItemFromTeamMember(&PlayerBag, &team_mates[CURRENT_LEADER], ReviverSeed);
     //printf("Item on player now is %s\n", GetItemNameFromId(team_mates[CURRENT_LEADER].held_item));

        for (int i = 0; i < MAX_ITEMS; i++)
        {
            u32 item = rand_interval(0, 30);
            AddItemToBagByType(game->bag, item);
        }
        printf("Current bag size is %d\n", game->bag->size);

        //GiveItemToTeamMember(game->bag, &team_mates[CURRENT_LEADER], PowerBand);
        //RemoveItemFromTeamMemberToBag(game->bag, &team_mates[CURRENT_LEADER], PowerBand);
        //RemoveItemFromBag_(game->bag, "PowerBand");
        //RemoveItemFromBag_(game->bag, "ReviverSeed");
        //RemoveItemFromBag_(game->bag, "ReviverSeed");
        //RemoveItemFromBag_(game->bag, "OranBerry");
        //RemoveItemFromBag_(game->bag, "OranBerry");
        //RemoveItemFromBag_(game->bag, "OranBerry");
        //RemoveItemFromBag_(game->bag, "OranBerry");
        //printf("Current bag size is %d\n", game->bag->size);
        //SetUpDefualtStatus();
        //AddItemToBag_(game->bag, "Apple");
        //UseItemFromBag(game->bag, &team_mates[CURRENT_LEADER], Apple);
        //AddItemToBag_(game->bag, "Apple");
        //AddItemToBag_(game->bag, "Apple");
        //AddItemToBag_(game->bag, "Apple");
        //AddItemToBag_(game->bag, "Apple");
        //AddItemToBag_(game->bag, "Apple");
        //RemoveItemFromBag_(game->bag, "JoySeed");
        //RemoveItemFromBag_(game->bag, "JoySeed");
        //printf("Current bag size is %d\n", game->bag->size);

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
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        printf("Bag before Sort\n");
        DisplayBag(game->bag);
        printf("Sorting Bag!\n");
        Bag_SortItems(game->bag);
        Bag_CountSortItemsDesc(game->bag, game->bag->size, 174);
        DisplayBag(game->bag);
        printf("Current bag size is %d\n", game->bag->size);
    }
    //else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    //{
    //    printf("Removing JoySeed\n");
    //    RemoveItemFromBag_(game->bag, "JoySeed");
    //    DisplayBag(game->bag);
    //}
    
}

Game_t *Game_New(bool init)
{
    Game_t *game = (Game_t*) malloc(sizeof(*game));

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
    Sprite_MakeTextureAtlas();
    self->screen  = Screen_New(true);
    self->player  = Player_New(true);
    
    self->bag     = Bag_New(true);
    self->audio_state = ALState_New(512, false, true);

    Dungeon_Init(NULL);
    

    //self->party   = PokemonParty_New(4);

    //Pokemon *leader = Pokemon_New("TestName", Bulbasaur, Grass, Poison, Overgrow, Female, 5, 20);

    //AddPartyMember(self->party, leader);

    glfwSetWindowUserPointer(self->screen->window, self);
    glfwSetKeyCallback(self->screen->window, key_callback);
}

void Game_Update(Game_t *self)
{
    Player_Update(self->player);
    Screen_Update(self->screen);

    if (glfwWindowShouldClose(self->screen->window))
    {
        self->running = false;
    }

}

void Game_ShutDown(Game_t *self)
{
    Bag_ShutDown(self->bag);
    Player_ShutDown(self->player);
    Screen_Shutdown(self->screen);

    free(self);
}
