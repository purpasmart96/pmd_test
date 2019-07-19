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
#include "game_common/display.h"
#include "game_common/tile.h"

// The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;
// Maximum axis velocity of the dot
static const int DOT_VEL = 10;

// The dimensions of the level
static const int LEVEL_WIDTH = 1280;
static const int LEVEL_HEIGHT = 960;

static const int TILE_WIDTH = 80;
static const int TILE_HEIGHT = 80;
static const int TOTAL_TILES = 192;
static const int TOTAL_TILE_SPRITES = 12;

// The different tile sprites
static const int TILE_RED = 0;
static const int TILE_GREEN = 1;
static const int TILE_BLUE = 2;
static const int TILE_CENTER = 3;
static const int TILE_TOP = 4;
static const int TILE_TOPRIGHT = 5;
static const int TILE_RIGHT = 6;
static const int TILE_BOTTOMRIGHT = 7;
static const int TILE_BOTTOM = 8;
static const int TILE_BOTTOMLEFT = 9;
static const int TILE_LEFT = 10;
static const int TILE_TOPLEFT = 11;


static int Tile_GetType(Tile *self)
{
    return self->type;
}

static SDL_Rect Tile_GetBox(Tile *self)
{
    return self->box;
}

Tile *Tile_New(int x, int y, int tile_type)
{
    Tile *tile = (Tile*) malloc(sizeof(*tile));

    tile->box.x = x;
    tile->box.y = y;
    tile->box.w = TILE_WIDTH;
    tile->box.h = TILE_HEIGHT;
    tile->type = tile_type;

    return tile;
}

bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    // Calculate the sides of rect A
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    // Calculate the sides of rect B
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottom_a <= top_b)
    {
        return false;
    }
    else if (top_a >= bottom_b)
    {
        return false;
    }
    else if (right_a <= left_b)
    {
        return false;
    }
    else if (left_a >= right_b)
    {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}

bool TouchesWall(SDL_Rect box, Tile *tiles[])
{
    // Go through the tiles
    for (int i = 0; i < TOTAL_TILES; ++i)
    {
        // If the tile is a wall type tile
        if ((tiles[i]->type >= TILE_CENTER) && (tiles[i]->type <= TILE_TOPLEFT))
        {
            // If the collision box touches the wall tile
            if (CheckCollision(box, tiles[i]->box))
            {
                return true;
            }
        }
    }
    // If no wall tiles were touched
    return false;
}


void Dot_Move(Dot *self, Tile *tiles[])
{
    // Move the dot left or right
    self->box.x += self->mVelX;
    // If the dot went too far to the left or right or touched a wall
    if ((self->box.x < 0) || (self->box.x + DOT_WIDTH > LEVEL_WIDTH) || TouchesWall(self->box, tiles))
    {
        // move back
        self->box.x -= self->mVelX;
    }

    // Move the dot up or down
    self->box.y += self->mVelY;

    // If the dot went too far up or down or touched a wall
    if ((self->box.y < 0) || (self->box.y + DOT_HEIGHT > LEVEL_HEIGHT) || TouchesWall(self->box, tiles))
    {
        // move back
        self->box.y -= self->mVelY;
    }
}


void Dot_SetCamera(Dot *self, SDL_Rect camera)
{
    //Center the camera over the dot
    camera.x = (self->box.x + DOT_WIDTH / 2) - 1280 / 2;
    camera.y = (self->box.y + DOT_HEIGHT / 2) - 720 / 2;

    // Keep the camera in bounds
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Dot_Render(Screen_t *screen, Dot *self, SDL_Rect camera)
{
    //Show the dot
    //gDotTexture.render(self->box.x - camera.x, self->box.y - camera.y);
}