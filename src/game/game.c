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
#include <pthread.h>

#include "common/vec.h"
#include "common/list_generic.h"
#include "common/rand_num.h"
#include "common/timer.h"

#include "audio_core/sound_core.h"

#include "game/dungeon.h"
#include "game/move.h"
#include "game/pokemon.h"
#include "game/display.h"
#include "game/sprites.h"
#include "game/input.h"
#include "game/player.h"
#include "game/item.h"
#include "game/game.h"
#include "game/renderer.h"

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


static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Game_t *game = glfwGetWindowUserPointer(window);

    game->player->input->mouse_x = xpos;
    game->player->input->mouse_y = ypos;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Game_t *game = glfwGetWindowUserPointer(window);
    
    game->player->input->buttons[button] = action != GLFW_RELEASE;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Game_t *game = glfwGetWindowUserPointer(window);

    game->player->input->keys[key] = action != GLFW_RELEASE;
    //game->player->input->current_key = key;
    //game->player->input->scan_code = scancode;
    //game->player->input->action = action;
    //game->player->input->mods = mods;

    //Player_Update(game->player);
    
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //SoundInfo *si = ogg_decode("D:/PokeMysteryDun/pmd_fix/data/sound/bgm/Aegis Cave.ogg");
        
        // TODO
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
    


        //for (int i = 0; i < MAX_ITEMS; i++)
        //{
        //    u32 item = rand_interval(67, 69);
        //    AddItemToBagByType(game->bag, item);
        //}
        //printf("Current bag size is %d\n", game->bag->size);

        //DisplayBag(game->bag);
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        //srand(time(NULL));
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            u32 item = rand_interval(67, 69);
            AddItemToBagByType(game->bag, item);
        }

        AddItemToBagByType(game->bag, OranBerry);
        //AddItemToBagByType(game->bag, OranBerry);
        //AddItemToBagByType(game->bag, OranBerry);
        //AddItemToBagByType(game->bag, OranBerry);
        //AddItemToBagByType(game->bag, SitrusBerry);
        //AddItemToBagByType(game->bag, SitrusBerry);
        //AddItemToBagByType(game->bag, SitrusBerry);
        //AddItemToBagByType(game->bag, SitrusBerry);
        //AddItemToBagByType(game->bag, JoySeed);
        //AddItemToBagByType(game->bag, ReviverSeed);
        //AddItemToBagByType(game->bag, ReviverSeed);
        //AddItemToBagByType(game->bag, ReviverSeed);
        //AddItemToBagByType(game->bag, ReviverSeed);
        //AddItemToBagByType(game->bag, PechaBerry);

        printf("Current bag size is %d\n", game->bag->real_size);

        //DisplayBag(game->bag);

        printf("Bag before Sort\n");
        DisplayBag(game->bag);
        printf("Sorting Bag!\n");
        Bag_SortItems(game->bag);
        //Bag_CountSortItemsDesc(game->bag, game->bag->size, 174);
        DisplayBag(game->bag);
        printf("Current bag size is %d\n", game->bag->real_size);
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
        //DisplayBag(game->bag);
        RemovePartyMemberByName(game->party, "Garchomp");

        struct Pokemon_s *teamate = Pokemon_New("Garchomp", Garchomp, Dragon, Ground, RoughSkin, Female, 55, 255, false);
        teamate->current_hp = 110;
        teamate->attack = 92;
        teamate->defense = 76;
        AddPartyMember(game->party, teamate);
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

static pthread_t thread;

void Game_Init(Game_t *self)
{
    self->running = true;
    self->time_info = TimeInfo_New();
    //self->delta_time = 0.0;
    self->accumulator = 0;
    self->alpha = 0;
    self->current_time = 0.0;
    self->frames = 0;
    self->updates = 0;
    self->previous_time = glfwGetTime();
    self->timer = self->previous_time;
    Sprite_LoadAllTextures();
    Dungeon_Init(NULL, 5);
    //self->screen  = Screen_New(true);
    //self->player  = Player_New(true);

    //pthread_create(&thread, NULL, Screen_Update, NULL);
    //self->screen = GetScreenInstance();
    //self->player = GetPlayerInstance();
    self->screen = Screen_New(true);
    self->player = Player_New(true);

    self->party = PokemonParty_New(4);
    AddPartyMember(self->party, self->player->leader);
    struct Pokemon_s *teamate = Pokemon_New("Garchomp", Garchomp, Dragon, Ground, RoughSkin, Female, 55, 255, true);
    teamate->current_hp = 110;
    teamate->attack = 92;
    teamate->defense = 76;

    AddPartyMember(self->party, teamate);
    
    self->bag = Bag_New(true);
    self->audio_state = ALState_New(512, false, true);


    glfwSetWindowUserPointer(self->screen->window, self);
    glfwSetKeyCallback(self->screen->window, key_callback);
    glfwSetMouseButtonCallback(self->screen->window, mouse_button_callback);
    glfwSetCursorPosCallback(self->screen->window, cursor_position_callback);

    //Renderer_StartThread(self->screen->renderer);
}

//static double GetDeltaTime(Game_t *self, struct timeval *end)
//{
//    double time = glfwGetTime();
//    gettimeofday(end, NULL);
//
//    int milliseconds_start = self->current_time / 1000;
//    int milliseconds_end = end->tv_usec / 1000;
//
//    int min_ms = MIN(milliseconds_end, milliseconds_start);
//    int max_ms = MAX(milliseconds_end, milliseconds_start);
//    int delta_time = (max_ms - min_ms);
//    return (double)delta_time;
//}
//
//static void UpdateDeltaTime(Game_t *self, struct timeval *end)
//{
//    glfwSetTime(0.0);
//    self->current_time = end->tv_usec;
//}

//static double GetDeltaTime(Game_t *self)
//{
//    double time = glfwGetTime();
//    double delta = (time - self->previous_time);
//    self->previous_time = time;
//    return delta;
//}


// The sum computed by the background thread
long long sum = 0;

// Thread function to generate sum of 0 to N
void* ThreadFuncTest(void* arg)
{
    long long *limit_ptr = (long long*)arg;
    long long limit = *limit_ptr;

    for (long long i = 0; i <= limit; i++) {
        sum += i;
    }

    // sum is a global variable, so other threads can access.

    pthread_exit(0);
}

void Game_Update(Game_t *self)
{
    double delta_time = GetDeltaTime(self->time_info);

    self->time_info->accumulator += delta_time;

    while (self->time_info->accumulator >= FPS_LIMIT)
    {
        //glfwPollEvents();
        //pthread_join(thread, NULL);
        Player_Update(self->player);
        //Screen_Update(self->screen);
        //self->frames++;
        self->updates++;
        self->time_info->accumulator -= FPS_LIMIT;
    }

    self->time_info->alpha = self->time_info->accumulator / FPS_LIMIT;
    Screen_Update(self->screen, Player_GetPosition(self->player));
    self->frames++;

    if (glfwGetTime() - self->time_info->timer > 1.0)
    {
        self->time_info->timer += 1.0;

        printf("ups %llu, fps %llu\n", self->updates, self->frames);

        self->updates = 0;
        self->frames = 0;
    }

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
    Player_ShutDown(self->player, thread);
    Screen_ShutDown(self->screen);

    free(self);
}
