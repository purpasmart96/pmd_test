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

#include "game_common/game.h"
#include "game_common/pokemon.h"
#include "game_common/input.h"
#include "game_common/player.h"
#include "game_common/dungeon.h"

// Do not modify, this is just for getting values outside player.c
static ivec2 player_position;

Player_t *Player_New(bool init)
{
    Player_t *player = malloc(sizeof(*player));

    if (!player)
    {
        return NULL;
    }
    else if (init)
    {
        Player_Init(player);

    }
    return player;
}


void Player_Init(Player_t *self)
{
    self->prev_update = glfwGetTime();
    self->leader = Pokemon_New("Flygon", Flygon, Dragon, Ground, Levitate, Female, 45, 255, true);
    self->leader->current_hp = 100;
    self->leader->attack = 72;
    self->leader->defense = 66;

    self->input = Input_New(true);
}

static void MovePlayerXAxis(Player_t *self, Dungeon *dungeon, Direction direction, int position_delta)
{
    TileState tile = GetTileInFront(dungeon, self->leader->position, direction);
    if (IsTilePassableByType(dungeon->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position);
        self->leader->position.x += position_delta;
        
        SetPlayerTile(dungeon, self->leader->position);
    }
}

static MovePlayerYAxis(Player_t *self, Dungeon *dungeon, Direction direction, int position_delta)
{
    TileState tile = GetTileInFront(dungeon, self->leader->position, direction);
    if (IsTilePassableByType(dungeon->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position);
        self->leader->position.y += position_delta;
        
        SetPlayerTile(dungeon, self->leader->position);
    }
}

static bool DoneWaiting()
{
    u64 current_frames_updated = Game_GetTicks();
    return current_frames_updated % 10 == 0;
}

static void MoveLeft(Player_t *self, Dungeon *dungeon)
{
    MovePlayerXAxis(self, dungeon, West, -1);
    DEBUG("Player position X %d\n", self->leader->position.x);
}

static void MoveRight(Player_t *self, Dungeon *dungeon)
{
    MovePlayerXAxis(self, dungeon, East, 1);
    DEBUG("Player position X %d\n", self->leader->position.x);
}

static void MoveDown(Player_t *self, Dungeon *dungeon)
{
    MovePlayerYAxis(self, dungeon, South, -1);
    DEBUG("Player position Y %d\n", self->leader->position.y);
}

static void MoveUp(Player_t *self, Dungeon *dungeon)
{
    MovePlayerYAxis(self, dungeon, North, 1);
    DEBUG("Player position Y %d\n", self->leader->position.y);
}

static void HandleButtunPress(Player_t *self)
{
    Dungeon *dungeon = GetDungeonObject();

    if (Input_IsKeyPressed(self->input, GLFW_KEY_S))
    {
        MoveDown(self, dungeon);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_A))
    {
        MoveLeft(self, dungeon);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_W))
    {
        MoveUp(self, dungeon);
    }

    if (Input_IsKeyPressed(self->input, GLFW_KEY_D))
    {
        MoveRight(self, dungeon);
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

static void Player_SetPosition(Player_t *self)
{
    player_position = self->leader->position;
}

static void Player_Move(Player_t *self)
{
    HandleButtunPress(self);
    Player_SetPosition(self);
}

ivec2 Player_GetPosition()
{
    return player_position;
}

void Player_Update(Player_t *self, u64 delta_time)
{
    glfwPollEvents();

    //double time  = glfwGetTime();

    //double delta = (time - self->prev_update);


    //double new_delta = delta_time * 10000.0;
    //bool update = delta_time % 5 == 0;
    //if (delta >= PLAYER_MOVEMENT_SPEED)
    //{
        Player_Move(self);
    //    self->prev_update = time;
    //}
    //glfwWaitEvents();
}

void Player_ShutDown(Player_t *self)
{
    Input_ShutDown(self->input);
    free(self->leader->status);
    free(self->leader);
    free(self);
}
