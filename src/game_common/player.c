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

#include "game_common/pokemon.h"
#include "game_common/input.h"
#include "game_common/player.h"
#include "game_common/dungeon.h"

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
    self->leader = Pokemon_New("Flygon", Flygon, Dragon, Ground, Levitate, Female, 45, 255, true);
    self->leader->current_hp = 100;
    self->leader->attack = 72;
    self->leader->defense = 66;

    self->input = Input_New(true);
}

static void MovePlayerXAxis(Player_t *self, Direction direction, int position_delta)
{
    TileState tile = GetTileInFront(GetDungeonObject(), self->leader->position, direction);
    if (IsTilePassableByType(GetDungeonObject()->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position.x, self->leader->position.y);
        self->leader->position.x += position_delta;
        
        SetPlayerTile(GetDungeonObject(), self->leader->position.x, self->leader->position.y);
    }
}

static MovePlayerYAxis(Player_t *self, Direction direction, int position_delta)
{
    TileState tile = GetTileInFront(GetDungeonObject(), self->leader->position, direction);
    if (IsTilePassableByType(GetDungeonObject()->floor, tile.tile))
    {
        SetPlayerPreviousPos(self->leader->position.x, self->leader->position.y);
        self->leader->position.y += position_delta;
        
        SetPlayerTile(GetDungeonObject(), self->leader->position.x, self->leader->position.y);
    }
}

static void MoveLeft(Player_t *self)
{
    MovePlayerXAxis(self, West, -1);
    DEBUG("Player position X %d\n", self->leader->position.x);
}

static void MoveRight(Player_t *self)
{
    MovePlayerXAxis(self, East, 1);
    DEBUG("Player position X %d\n", self->leader->position.x);
}

static void MoveDown(Player_t *self)
{
    MovePlayerYAxis(self, South, -1);
    DEBUG("Player position Y %d\n", self->leader->position.y);
}

static void MoveUp(Player_t *self)
{
    MovePlayerYAxis(self, North, 1);
    DEBUG("Player position Y %d\n", self->leader->position.y);
}

static void HandleButtunPress(Player_t *self)
{
    switch (self->input->current_key)
    {
        case GLFW_KEY_S:
            MoveDown(self);
            break;
        case GLFW_KEY_A:
            MoveLeft(self);
            break;
        case GLFW_KEY_W:
            MoveUp(self);
            break;
        case GLFW_KEY_D:
            MoveRight(self);
            break;
        default:
            break;
    }
}

static void Player_Move(Player_t *self)
{
    if (self->input->action == GLFW_PRESS || self->input->action == GLFW_REPEAT)
    {
        HandleButtunPress(self);
    }
}

void Player_Update(Player_t *self)
{
    glfwPollEvents();
    Player_Move(self);

    //glfwWaitEvents();
}

void Player_ShutDown(Player_t *self)
{
    Input_ShutDown(self->input);
    free(self->leader->status);
    free(self->leader);
    free(self);
}
