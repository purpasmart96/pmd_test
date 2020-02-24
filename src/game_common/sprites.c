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
#include <GL/glew.h>
#include <glfw3.h>
#include <lodepng.h>
#include "common/vec.h"
#include "common/strlcat.h"

#include "common/list_generic.h"

#include "game_common/renderer.h"
#include "game_common/sprites.h"

static const char *dir = "data/sprites/tiles/";
static char path[256] = { '\0' };

static ListTexture *texture_list = NULL;

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 480

static const char *background_sprites[] =
{
    "empty.png",
    "alpha.png",
    "dirt.png",
    "grass.png",
    "sand.png",
    "stone.png",
    "stairs_desc.png",
    "dark_crater_ground_middle.png",
    "dark_crater_wall_left.png",
    "dark_crater_wall_right.png",
    "dark_crater_lava_border_top_left.png",
    "dark_crater_lava_border_top_middle.png",
    "dark_crater_lava_border_top_right.png",
    "dark_crater_lava_border_middle_left.png",
    "dark_crater_lava_middle.png",
    "dark_crater_lava_border_middle_right.png",
    "dark_crater_lava_border_bottom_left.png",
    "dark_crater_lava_border_bottom_middle.png",
    "dark_crater_lava_border_bottom_right.png",
    "volcano_ground.png",
    "water.png",
    "test.png",
    "test2.png",
    "flygon_front_facing_alpha.png",
    "flygon_front_facing2_alpha.png",
};


Texture_t *Texture_New(const char *name, u8 *image, GLuint internal_format, GLuint image_format, GLuint wrap_s, GLuint wrap_t, GLuint filter_min,
                       GLuint filter_max, u32 width, u32 height)
{
    Texture_t *texture = malloc(sizeof(*texture));
    texture->name = name;
    texture->image = image;
    texture->internal_format = internal_format;
    texture->image_format = image_format;
    texture->wrap_s = wrap_s;
    texture->wrap_t = wrap_t;
    texture->filter_min = filter_min;
    texture->filter_max = filter_max;
    texture->width = width;
    texture->height = height;

    return texture;
}

void Texture_Delete(Texture_t *texture)
{
    //free(texture);
}

u32 Texture_GetWidth(Texture_t *texture)
{
    return texture->width;
}

u32 Texture_GetHeight(Texture_t *texture)
{
    return texture->height;
}

void Texture_Bind(Texture_t *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void Texture_Unbind(Texture_t *texture)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Should probably just look up textures by their id's instead of their filename...
static Texture_t *GetTextureFromListByName(const char *name)
{
    for (int i = 0; i < texture_list->count; i++)
    {
        Texture_t *temp = LIST_AT(ListTexture, texture_list, i);

        if (strcmp(temp->name, name) == 0)
        {
            return temp;
        }
    }
}

Texture_t *LoadTexture(const char *name)
{
    Texture_t *texture = GetTextureFromListByName(name);
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_t);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_min);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_max);

    glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_format, texture->width, texture->height, 0, texture->image_format, GL_UNSIGNED_BYTE, texture->image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void Sprites_BindTexture(Texture_t *texture, int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

static void Sprite_LoadTextureIntoList(const char *name)
{
    u32 error;
    u8 *image;
    u32 width, height;

    char path[256] = {'\0' };
    strlcat(path, dir, sizeof(path));
    strlcat(path, name, sizeof(path));
    error = lodepng_decode32_file(&image, &width, &height, path);
    if (error)
    {
        ERROR("%u: %s\n", error, lodepng_error_text(error));
    }
    
    LIST_PUSH(ListTexture, texture_list, Texture_New(name, image, GL_RGBA, GL_RGBA, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_NEAREST, GL_NEAREST,  width, height));
}

void Sprite_LoadAllTextures(void)
{
    texture_list = LIST_NEW(ListTexture);

    for (int i = 0; i < ARRAY_SIZE(background_sprites); i++)
    {
        Sprite_LoadTextureIntoList(background_sprites[i]);
    }
    DEBUG("Finished loading textures into list\n");
}
