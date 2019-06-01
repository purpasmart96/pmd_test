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
#include "common/vec.h"
#include "common/strlcat.h"
#include "common/lodepng.h"
#include "common/list_generic.h"

#include "game_common/shader.h"
#include "game_common/sprites.h"

static const char *dir = "data/sprites/tiles/";
static char path[64] = { '\0' };

static ListTexture *texture_list = NULL;

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 480

static const char *background_sprites[] =
{
    "empty.png",
    "dirt.png",
    "grass.png",
    "sand.png",
    "stone.png",
    "water.png",
    "test.png",
    "test2.png",
};

static int current_texture = 0;

typedef struct Coords_s
{
    int x;
    int y;
    int w;
    int h;
} Coords_t;

void SpriteRenderer_DrawSprite(Sprites_t *self, Texture_t *texture, vec2 position, vec2 size, GLfloat rotate, vec3 color)
{
    //Shader_Use(self);

    //mat4 model = mat4_translate(model, position.x, position.y, 0.0f, 0.0f);

    //model = mat4_translate(model, 0.5f * size.x, 0.5f * size.y, 0.0f);
    //model = mat4_rotate(model, rotate, 0.0f, 0.0f, 1.0f);
    //model = mat4_translate(model, -0.5f * size.x, -0.5f * size.y, 0.0f);

    //model = mat4_scale_xyz(model, size.x, size.y, 1.0f);

    //Shader_SetMatrix4(self, "model", &model);
    //Shader_SetVector3f(self, "vertex_color", &color);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture->id);

    ////glBindVertexArray(self->shader->vao->);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glBindVertexArray(0);
}


Sprites_t *Sprites_New(bool init)
{
    Sprites_t *sprites = malloc(sizeof(*sprites));

    if (!sprites)
    {
        return NULL;
    }
    else if (init)
    {
        Sprites_Init(sprites);
    }

    return sprites;
}


void Sprites_Init(Sprites_t *self)
{
    //// Configure VAO/VBO
    //GLuint VBO;
    //GLfloat vertices[] = {
    //    // Pos      // Tex
    //    0.0f, 1.0f, 0.0f, 1.0f,
    //    1.0f, 0.0f, 1.0f, 0.0f,
    //    0.0f, 0.0f, 0.0f, 0.0f,

    //    0.0f, 1.0f, 0.0f, 1.0f,
    //    1.0f, 1.0f, 1.0f, 1.0f,
    //    1.0f, 0.0f, 1.0f, 0.0f
    //};

    //glGenVertexArrays(1, &self->shader->vao);
    //glGenBuffers(1, &VBO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindVertexArray(self->shader->vao);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);



    //int scale_x = 1920 / VIRTUAL_WIDTH;
    //int scale_y = 1080 / VIRTUAL_HEIGHT;
    //mat4 sprite_matrix = { 0 };
    //mat4 matrix = mat4_scale_xyz(sprite_matrix, scale_x, scale_y, 1.0f);

    //_spriteBatch.Begin(transformMatrix: matrix);
}


Texture_t *Texture_New(const char *name, u8 *image,GLuint internal_format, GLuint image_format, GLuint wrap_s, GLuint wrap_t, GLuint filter_min,
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

Texture_t *LoadTexture(Texture_t *texture, const char *name)
{
    texture = GetTextureFromListByName(name);
    GLuint tex;
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_format, texture->width, texture->height, 0, texture->image_format, GL_UNSIGNED_BYTE, texture->image);
    glGenSamplers(1, &texture->sampler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

void Sprites_BindTexture(Texture_t *texture, int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glBindSampler(texture_unit, texture->sampler);
}

static void Sprite_LoadTextureIntoList(const char *name)
{
    u32 error;
    u8 *image;
    u32 width, height;

    char path[64] = {'\0' };
    strlcat(path, dir, sizeof(path));
    strlcat(path, name, sizeof(path));
    error = lodepng_decode32_file(&image, &width, &height, path);
    if (error)
    {
        ERROR("%u: %s\n", error, lodepng_error_text(error));
    }
    
    LIST_PUSH(ListTexture, texture_list, Texture_New(name, image, GL_RGBA, GL_RGBA, GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR,  width, height));
}

void Sprite_MakeTextureAtlas(void)
{
    texture_list = LIST_NEW(ListTexture);

    for (int i = 0; i < ARRAY_SIZE(background_sprites); i++)
    {
        Sprite_LoadTextureIntoList(background_sprites[i]);
    }
    DEBUG("Finished loading textures into list\n");
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
