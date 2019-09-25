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
#include <glfw3.h>

#include "common/vec.h"
#include "common/list_generic.h"
#include "common/rand_num.h"

#include "audio_core/sound_core.h"

#include "game_common/dungeon.h"
#include "game_common/move.h"
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

    game->player->input->current_key = key;
    game->player->input->scan_code = scancode;
    game->player->input->action = action;
    game->player->input->mods = mods;

    Player_Update(game->player);
    
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
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


        for (int i = 0; i < MAX_ITEMS; i++)
        {
            u32 item = rand_interval(67, 69);
            AddItemToBagByType(game->bag, item);
        }
        printf("Current bag size is %d\n", game->bag->size);

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
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        CalculateDamage(KarateChop, game->player->leader, game->player->leader, true);
        UseItemFromBag(game->bag, game->party, game->player->leader, "OranBerry");
        //CalculateDamage(KarateChop, game->player->leader, game->player->leader, false);

        //RemoveItemFromBag_(game->bag, "JoySeed");
        //DisplayBag(game->bag);
    }
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
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
    Sprite_LoadAllTextures();
    self->screen  = Screen_New(true);
    Dungeon_Init(NULL);
    self->player  = Player_New(true);
    self->party = PokemonParty_New(4);
    AddPartyMember(self->party, self->player->leader);
    
    self->bag     = Bag_New(true);
    self->audio_state = ALState_New(512, false, true);


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
    Dungeon_ShutDown();
    Bag_ShutDown(self->bag);
    PokemonParty_Destroy(self->party);
    Player_ShutDown(self->player);
    Screen_ShutDown(self->screen);

    free(self);
}
