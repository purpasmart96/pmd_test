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

#ifndef _TILE_MANAGER_H_
#define _TILE_MANAGER_H_

#include <SDL.h>

typedef struct Tile
{
    SDL_Rect box;
    // Initializes position and type
    // Tile( int x, int y, int tileType );
    // The attributes of the tile
    // The tile type
    int type;
} Tile;

// The dot that will move around on the screen
typedef struct Dot
{
    // Takes key presses and adjusts the dot's velocity

    // Collision box of the dot
    SDL_Rect box;
    // The velocity of the dot
    int mVelX, mVelY;
} Dot;

void(*Handle_Event)(SDL_Event e);
// Moves the dot and check collision against tiles
void Dot_Move(Dot *self, Tile *tiles[]);
// Centers the camera over the dot
void Dot_SetCamera(Dot *self, SDL_Rect camera);
// Shows the dot on the screen
void Dot_Render(Screen_t *screen, Dot *self, SDL_Rect camera);

#endif
