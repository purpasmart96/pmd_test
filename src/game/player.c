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
#include "common/timer.h"

#include "game/game.h"
#include "game/pokemon.h"
#include "game/input.h"
#include "game/player.h"
#include "game/dungeon.h"

static float velocity = 12;

//static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//static volatile struct Player_s* volatile player_instance = NULL;
//
//// singleton Double check lock, might be a meme and still not be thread safe
//Player_t *GetPlayerInstance()
//{
//    // putting a pre condition to avoid locks on multiple calls
//    // if we don't put this condition,_lock.acquire()and _lock.release() will always be executed on 
//    // multiple GetInstance() call and will affect performance.
//    if (player_instance == NULL)
//    {
//        pthread_mutex_lock(&lock);
//
//        if (player_instance == NULL)
//        {
//            player_instance = Player_New(true);
//        }
//        pthread_mutex_unlock(&lock);
//    }
//    return player_instance;
//}

Player_t *Player_New()
{
    Player_t *player = malloc(sizeof(*player));

    if (!player)
    {
        return NULL;
    }
    else
    {
        Player_Init(player);

    }
    return player;
}

void Player_Init(Player_t *self)
{
    self->prev_update = glfwGetTime();
    self->time_info = TimeInfo_New();
    self->leader = Pokemon_New("Flygon", Flygon, Dragon, Ground, Levitate, Female, 45, 255, true);
    self->leader->current_hp = 100;
    self->leader->attack = 72;
    self->leader->defense = 66;

    self->input = Input_New(true);
}

vec2 Player_GetPosition(Player_t *self)
{
    return self->leader->position;
}

static void MovePlayerXAxis(Player_t *self, Dungeon *dungeon, Direction direction, float position_delta, float alpha)
{
    TileState tile = GetTileInFront(dungeon, self->leader->position, direction);
    if (IsTilePassableByType(dungeon->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position);
        self->leader->prev_position = self->leader->position;

        self->leader->position.x += position_delta * velocity * TIME_STEP;
        //self->leader->position.x = LinearInterpolation(self->leader->prev_position.x, self->leader->position.x, alpha * 1000);
        
        SetPlayerTile(dungeon, self->leader->position);
    }
}

static MovePlayerYAxis(Player_t *self, Dungeon *dungeon, Direction direction, float position_delta, float alpha)
{
    TileState tile = GetTileInFront(dungeon, self->leader->position, direction);
    if (IsTilePassableByType(dungeon->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position);
        self->leader->prev_position = self->leader->position;

        self->leader->position.y += position_delta * velocity * TIME_STEP;
        //self->leader->position.y = LinearInterpolation(self->leader->prev_position.y, self->leader->position.y, alpha * 1000);
        
        SetPlayerTile(dungeon, self->leader->position);
    }
}

static bool DoneWaiting()
{
    u64 current_frames_updated = Game_GetTicks();
    return current_frames_updated % 10 == 0;
}

static void MoveLeft(Player_t *self, Dungeon *dungeon, float alpha)
{
    MovePlayerXAxis(self, dungeon, West, -1.0, alpha);
    DEBUG("Player position X %f\n", self->leader->position.x);
}

static void MoveRight(Player_t *self, Dungeon *dungeon, float alpha)
{
    MovePlayerXAxis(self, dungeon, East, 1.0, alpha);
    DEBUG("Player position X %f\n", self->leader->position.x);
}

static void MoveDown(Player_t *self, Dungeon *dungeon, float alpha)
{
    MovePlayerYAxis(self, dungeon, South, -1.0, alpha);
    DEBUG("Player position Y %f\n", self->leader->position.y);
}

static void MoveUp(Player_t *self, Dungeon *dungeon, float alpha)
{
    MovePlayerYAxis(self, dungeon, North, 1.0, alpha);
    DEBUG("Player position Y %f\n", self->leader->position.y);
}

static void HandleButtunPress(Player_t *self, float alpha)
{
    Dungeon *dungeon = GetDungeonObject();

    if (Input_IsKeyPressed(self->input, GLFW_KEY_A))
    {
        MoveLeft(self, dungeon, alpha);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_D))
    {
        MoveRight(self, dungeon, alpha);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_S))
    {
        MoveDown(self, dungeon, alpha);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_W))
    {
        MoveUp(self, dungeon, alpha);
    }

    //switch (self->input->current_key)
    //{
    //    case GLFW_KEY_S:
    //        MoveDown(self, dungeon);
    //        break;
    //    case GLFW_KEY_A:
    //        MoveLeft(self, dungeon);
    //        break;
    //    case GLFW_KEY_W:
    //        MoveUp(self, dungeon);
    //        break;
    //    case GLFW_KEY_D:
    //        MoveRight(self, dungeon);
    //        break;
    //    default:
    //        break;
    //}
}

static void Player_Move(Player_t *self, float alpha)
{
    HandleButtunPress(self, alpha);
}

void Player_Update(Player_t *self, float alpha)
{
    glfwPollEvents();

    //double time  = glfwGetTime();

    //double delta = (time - self->prev_update);


    //double new_delta = delta_time * 10000.0;
    //bool update = delta_time % 5 == 0;
    //if (delta >= PLAYER_MOVEMENT_SPEED)
    //{
        Player_Move(self, alpha);
    //    self->prev_update = time;
    //}
    //glfwWaitEvents();
}

//void Player_Update()
//{
//    Player_t *player = GetPlayerInstance();
//    player->exit = false;
//    while (!player->exit)
//    {
//        //Player_t *player = GetPlayerInstance();
//        double delta_time = GetDeltaTime(player->time_info);
//
//        player->time_info->accumulator += delta_time;
//
//        if (player->time_info->accumulator >= FPS_LIMIT)
//        {
//            Player_Move(player);
//            player->time_info->accumulator -= FPS_LIMIT;
//        }
//        player->time_info->alpha = player->time_info->accumulator / FPS_LIMIT;
//        //Player_Move(player);
//    }
//    pthread_exit(NULL);
//}

void Player_ShutDown(Player_t *self, pthread_t thread)
{
    //self->exit = true;
    //pthread_join(thread, NULL);
    Input_ShutDown(self->input);
    free(self->leader->status);
    free(self->leader);
    free(self);
}
