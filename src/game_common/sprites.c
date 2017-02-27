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
#include "common/strlcat.h"
#include "common/lodepng.h"
#include "common/list_generic.h"

static const char *dir = "data/sprites/tiles/";
static char path[64] = { '\0' };

static ListTexture *texture_list = NULL;

static const char *background_sprites[] =
{
    "None",
    "dirt.png",
    "grass.png",
    "sand.png",
    "stone.png",
    "water.png",
};

typedef struct Coords_s
{
    int x;
    int y;
    int w;
    int h;
} Coords_t;

Texture_t *Texture_New(u8 *image, u32 width, u32 height)
{
    Texture_t *texture = malloc(sizeof(*texture));
    texture->image = image;
    texture->width = width;
    texture->height = height;

    return texture;
}

void Sprite_MakeTextureAtlas(void)
{
    texture_list = LIST_NEW(ListTexture);
    //Texture_t **texture_atlas = malloc(sizeof(*texture_atlas) * sizeof(background_sprites));
    u32 error;
    u8 *image;
    u32 width, height;

    if (error)
    {
        ERROR("%u: %s\n", error, lodepng_error_text(error));
    }

    for (int i = 0; i < ARRAY_SIZE(background_sprites); i++)
    {
        strlcat(path, dir, sizeof(path));
        strlcat(path, background_sprites[i], sizeof(path));
        error = lodepng_decode32_file(&image, &width, &height, path);

        LIST_PUSH(ListTexture, texture_list, *Texture_New(image, width, height));
        memset(path, '\0', sizeof(path));
    }
}

/*
bool CheckCollision(Coords_t a, Coords_t b)
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
*/

/*
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
*/
