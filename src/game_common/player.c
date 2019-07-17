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

#include "game_common/pokemon.h"
#include "game_common/input.h"
#include "game_common/player.h"

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
    self->leader = Pokemon_New("Flygon", Flygon, Dragon, Ground, Levitate, Female, 25, 255);
    self->input = Input_New(true);
}

static void Player_Move(Player_t *self)
{
    if (self->input->action == GLFW_PRESS || self->input->action == GLFW_REPEAT)
    {
        if (Input_IsAPressed(self->input))
        {
            //if (Player->position.x <= self->screen->window->w - player->Size.x)
            //Player->position.x += velocity;
            if (self->leader->position.x > 0)
                self->leader->position.x--;
            DEBUG("Player position X %d\n", self->leader->position.x);
        }
        if (Input_IsDPressed(self->input))
        {
            self->leader->position.x++;
            DEBUG("Player position X %d\n", self->leader->position.x);
            //if (Player->position.x <= self->screen->window->w - player->Size.x)
            //Player->position.x += velocity;
            //self->keys[GLFW_KEY_D] = false;
        }
        if (Input_IsSPressed(self->input))
        {
            if (self->leader->position.y > 0)
                self->leader->position.y--;

            DEBUG("Player position Y %d\n", self->leader->position.y);
            //if (Player->position.x <= self->screen->window->w - player->Size.x)
            //Player->position.x += velocity;
            //self->keys[GLFW_KEY_S] = false;
        }
        if (Input_IsWPressed(self->input))
        {
            self->leader->position.y++;
            DEBUG("Player position Y %d\n", self->leader->position.y);
            //if (player->position.x >= 0)
            //player->position.x -= velocity;
            //self->keys[GLFW_KEY_W] = false;
        }
    }
}

void Player_Update(Player_t *self)
{
    //GLfloat velocity = 1; // PLAYER_VELOCITY * dt;
    glfwPollEvents();
    Player_Move(self);

    /*
    if (self->action == GLFW_PRESS || self->action == GLFW_REPEAT)
    {
    if (self->keys[GLFW_KEY_A])
    {
    DEBUG("Key A Pressed\n");
    //if (Player->position.x <= self->screen->window->w - player->Size.x)
    //Player->position.x += velocity;
    //self->keys[GLFW_KEY_A] = false;
    }
    else if (self->keys[GLFW_KEY_D])
    {
    DEBUG("Key D Pressed\n");
    //if (Player->position.x <= self->screen->window->w - player->Size.x)
    //Player->position.x += velocity;
    //self->keys[GLFW_KEY_D] = false;
    }
    else if (self->keys[GLFW_KEY_S])
    {
    DEBUG("Key S Pressed\n");
    //if (Player->position.x <= self->screen->window->w - player->Size.x)
    //Player->position.x += velocity;
    //self->keys[GLFW_KEY_S] = false;
    }
        else if (self->keys[GLFW_KEY_W])
        {
            DEBUG("Key W Pressed\n");
            //if (player->position.x >= 0)
            //player->position.x -= velocity;
            //self->keys[GLFW_KEY_W] = false;
        }
        else
        {
            ERROR("Unhandled Key Event 0X%X\n", self->current_key);
        }
    }

    */

    //glfwWaitEvents();
}

void Player_ShutDown(Player_t *self)
{
    Input_ShutDown(self->input);
    free(self);
}
