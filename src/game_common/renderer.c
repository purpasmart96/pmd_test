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
#include "common/list_generic.h"

#include "game_common/game.h"
#include "game_common/dungeon.h"
#include "game_common/sprites.h"
#include "game_common/player.h"
#include "game_common/vertex_buffer.h"
#include "game_common/index_buffer.h"
#include "game_common/vertex_array.h"
#include "game_common/camera.h"
#include "game_common/shader.h"
#include "game_common/renderer.h"

static mat4 ortho_matrix;
static mat4 model_matrix;
static mat4 view_matrix;

//struct VertexData
//{
//    GLfloat quad[12];
//    GLfloat quad_color[12];
//    GLfloat tex_coord[8];
//};

static Texture_t *sprite0;
static Texture_t *sprite1;
static Texture_t *sprite2;
static Texture_t *sprite3;
static Texture_t *sprite4;
static Texture_t *sprite5;
static Texture_t *sprite6;
static Texture_t *sprite7;
static Texture_t *sprite8;
static Texture_t *sprite9;

static Texture_t *sprite10;
static Texture_t *sprite11;
static Texture_t *sprite12;
static Texture_t *sprite13;
static Texture_t *sprite14;
static Texture_t *sprite15;
static Texture_t *sprite16;
static Texture_t *sprite17;

static void LoadBackgroundTextures()
{
    sprite0 = LoadTexture("empty.png");
    sprite1 = LoadTexture("empty.png");
    sprite2 = LoadTexture("dark_crater_wall_left.png");
    sprite3 = LoadTexture("dark_crater_wall_left.png");
    sprite4 = LoadTexture("dark_crater_ground_middle.png");
    sprite5 = LoadTexture("dark_crater_ground_middle.png");
    sprite6 = LoadTexture("stairs_desc.png");
    sprite7 = LoadTexture("dark_crater_lava_middle.png");
    sprite9 = LoadTexture("alpha.png");

    sprite10 = LoadTexture("dark_crater_lava_border_top_left.png");
    sprite11 = LoadTexture("dark_crater_lava_border_top_middle.png");
    sprite12 = LoadTexture("dark_crater_lava_border_top_right.png");
    sprite13 = LoadTexture("dark_crater_lava_border_bottom_left.png");
    sprite14 = LoadTexture("dark_crater_lava_border_bottom_middle.png");
    sprite15 = LoadTexture("dark_crater_lava_border_bottom_right.png");

    sprite16 = LoadTexture("dark_crater_lava_border_middle_left.png");
    sprite17 = LoadTexture("dark_crater_lava_border_middle_right.png");
}

static void LoadPlayerTextures()
{
    sprite8 = LoadTexture("flygon_front_facing_alpha.png");
}
static void LoadAllTextures()
{
    LoadBackgroundTextures();
    LoadPlayerTextures();
}

static void DeleteAllTextures()
{
    //Texture_Delete(sprite0);
    //Texture_Delete(sprite1);
    //Texture_Delete(sprite2);
    //Texture_Delete(sprite3);
    //Texture_Delete(sprite4);
    //Texture_Delete(sprite5);
    //Texture_Delete(sprite6);
    //Texture_Delete(sprite7);
    //Texture_Delete(sprite8);
    //Texture_Delete(sprite9);
}

Renderer_t *Renderer_New(bool init)
{
    Renderer_t *renderer = malloc(sizeof(*renderer));

    if (!renderer)
    {
        return NULL;
    }
    else if (init)
    {
        Renderer_Init(renderer);
    }

    return renderer;
}

static GLuint indices[] =
{
    0,1,2, // first triangle (bottom left - top left - top right)
    2,3,0 // second triangle (bottom left - top right - bottom right)
};

static GLfloat texcoords[] =
{
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

//static GLfloat texcoords[] =
//{
//    0.0f, 0.0f,
//    1.0f, 0.0f,
//    1.0f, 1.0f,
//    0.0f, 1.0f
//};

static GLfloat vertices[] = {
    // Pos  
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

void Renderer_DrawSprite(Renderer_t *self, Texture_t *texture, vec2 position, vec2 size, GLfloat rotate, vec3 color)
{
    mat4 model = mat4_identity();
    model = mat4_translate(model, position.x, position.y, 0.0f);

    model = mat4_translate(model, 0.5f * size.x, 0.5f * size.y, 0.0f);
    model = mat4_rotate(model, rotate, 0.0f, 0.0f, 1.0f);
    model = mat4_translate(model, -0.5f * size.x, -0.5f * size.y, 0.0f);

    model = mat4_scale_xyz(model, size.x, size.y, 1.0f);

    Shader_SetMatrix4(self->shader, "ModelMatrix", &model);
    Shader_SetVector3f(self->shader, "sprite_color", &color);
    Sprites_BindTexture(texture, 0);

    VertexArray_Bind(self->vao);
    //IndexBuffer_Bind(self->ibo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, self->ibo->count, GL_UNSIGNED_SHORT, 0);
    //IndexBuffer_Unbind(self->ibo);
    VertexArray_Unbind(self->vao);
}

static void Renderer_DrawSpriteLayers(Renderer_t *self, Texture_t *texture0, Texture_t *texture1, vec2 position, vec2 size, GLfloat rotate, vec3 color)
{
    mat4 model = mat4_identity();
    model = mat4_translate(model, position.x, position.y, 0.0f);

    model = mat4_translate(model, 0.5f * size.x, 0.5f * size.y, 0.0f);
    model = mat4_rotate(model, rotate, 0.0f, 0.0f, 1.0f);
    model = mat4_translate(model, -0.5f * size.x, -0.5f * size.y, 0.0f);

    model = mat4_scale_xyz(model, size.x, size.y, 1.0f);

    Shader_SetMatrix4(self->shader, "ModelMatrix", &model);
    Shader_SetVector3f(self->shader, "sprite_color", &color);
    Sprites_BindTexture(texture0, 0);
    Sprites_BindTexture(texture1, 1);

    VertexArray_Bind(self->vao);
    //IndexBuffer_Bind(self->ibo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, self->ibo->count, GL_UNSIGNED_INT, 0);
    //IndexBuffer_Unbind(self->ibo);
    VertexArray_Unbind(self->vao);
}

void Renderer_InitSprite(Renderer_t *self)
{
    self->vao = VertexArray_New();

    VertexBuffer_t *vbo_vertices = VertexBuffer_New(vertices, 6 * 2, 2);
    VertexBuffer_t *vbo_texcoords = VertexBuffer_New(texcoords, 6 * 2, 2);
    //self->ibo = IndexBuffer_New(indices, 6);

    const GLuint vertex_index = 0;
    const GLuint texcoords_index = 1;

    VertexArray_AddBuffer(self->vao, vbo_vertices, vertex_index);
    VertexArray_AddBuffer(self->vao, vbo_texcoords, texcoords_index);

}

static void DrawDungeonSprite(Renderer_t *self, Tile tile, vec2 position, vec2 sprite_size)
{
    switch (tile)
    {
        case tileUnused:
            Renderer_DrawSprite(self, sprite0, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileEnd:
            Renderer_DrawSprite(self, sprite1, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileWall:
            Renderer_DrawSprite(self, sprite2, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileWallLeft:
            Renderer_DrawSprite(self, sprite3, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileFloor:
            Renderer_DrawSprite(self, sprite4, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileHall:
            Renderer_DrawSprite(self, sprite5, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileStairs:
            Renderer_DrawSprite(self, sprite6, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLava:
            Renderer_DrawSprite(self, sprite7, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tilePlayer:
            Renderer_DrawSprite(self, sprite4, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            //Renderer_DrawSpriteLayer1(self, sprite0, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        default:
            break;
    }
}

static void DrawDungeonSpriteLayers(Renderer_t *self, Tile tile, vec2 position, vec2 sprite_size)
{
    switch (tile)
    {
        case tileUnused:
            Renderer_DrawSpriteLayers(self, sprite0, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileEnd:
            Renderer_DrawSpriteLayers(self, sprite1, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileWall:
            Renderer_DrawSpriteLayers(self, sprite2, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileWallLeft:
            Renderer_DrawSpriteLayers(self, sprite3, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileFloor:
            Renderer_DrawSpriteLayers(self, sprite4, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileHall:
            Renderer_DrawSpriteLayers(self, sprite5, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileStairs:
            Renderer_DrawSpriteLayers(self, sprite6, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLava:
            Renderer_DrawSpriteLayers(self, sprite7, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderUp:
            Renderer_DrawSpriteLayers(self, sprite11, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderRightUp:
            Renderer_DrawSpriteLayers(self, sprite12, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderLeftUp:
            Renderer_DrawSpriteLayers(self, sprite10, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderBottom:
            Renderer_DrawSpriteLayers(self, sprite14, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderBottomRight:
            Renderer_DrawSpriteLayers(self, sprite15, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderBottomLeft:
            Renderer_DrawSpriteLayers(self, sprite13, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderMiddleLeft:
            Renderer_DrawSpriteLayers(self, sprite16, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tileLavaBorderMiddleRight:
            Renderer_DrawSpriteLayers(self, sprite17, sprite9, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        case tilePlayer:
            Renderer_DrawSpriteLayers(self, sprite4, sprite8, position, sprite_size, 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
            break;
        default:
            break;
    }
}

static void DrawFloor(Renderer_t *renderer)
{
    Dungeon *dungeon = GetDungeonObject();
    for (int y = 0; y < dungeon->floor->height; y++)
    {
        for (int x = 0; x < dungeon->floor->width; x++)
        {
            float coord_x = x * 64.0f;
            float coord_y = y * 64.0f;

            bool is_coord_x_inside = coord_x <= 1280.0f;
            bool is_coord_y_inside = coord_y < 720.0f;

            if (is_coord_x_inside && is_coord_y_inside)
            {
                DrawDungeonSprite(renderer, dungeon->floor->tiles[x][y].tile, make_vec2(coord_x, coord_y),  make_vec2(64.0f, 64.0f));
            }
            else if (!is_coord_x_inside && !is_coord_y_inside)
            {
                return;
            }
        }
    }
}

static void DrawFloorAtPlayer(Renderer_t *renderer, vec2 sprite_size, float width, float height)
{
    // Find a  better way to pass this info
    ivec2 position = Player_GetPosition();

    struct Dungeon *dungeon = GetDungeonObject();

    // Offsets for drawing the player in the middle of the screen
    int new_x = position.x - 9; // 9 tiles
    int new_y = position.y - 5; // 5 Tiles

    for (int y = 0; y < dungeon->floor->height; y++)
    {
        for (int x = 0; x < dungeon->floor->width; x++)
        {
            float coord_x = x * sprite_size.x;
            float coord_y = y * sprite_size.y;

            bool is_coord_x_inside = coord_x < width;
            bool is_coord_y_inside = coord_y < height;

            if (is_coord_x_inside && is_coord_y_inside)
            {
                int new_coord_x = new_x + x;
                int new_coord_y = new_y + y;

                if (new_coord_x >= dungeon->floor->width || new_coord_y >= dungeon->floor->height || new_coord_x < 0 || new_coord_y < 0)
                {
                    DrawDungeonSpriteLayers(renderer, tileUnused, make_vec2(coord_x, coord_y), sprite_size);
                }
                else
                {
                    DrawDungeonSpriteLayers(renderer, dungeon->floor->tiles[new_coord_x][new_coord_y].tile, make_vec2(coord_x, coord_y), sprite_size);
                }

            }
            else if (!is_coord_x_inside && !is_coord_y_inside)
            {
                return;
            }
        }
    }
}

void Renderer_Init(Renderer_t *self)
{
    self->shader = Shader_New("data/shaders/sprite.vsh", "data/shaders/sprite.psh");
    Renderer_InitSprite(self);

    LoadAllTextures();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    self->camera = Camera_New(eye, center, up, 1280.0f, 720.0f);

    //ortho_matrix = mat4_identity();
    //model_matrix = mat4_identity();
    view_matrix = mat4_identity();
    //ortho_matrix = mat4_ortho(ortho_matrix, 0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    //vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    //vec3 center = make_vec3(1.0f, 1.0f, 0.0f);
    //vec3 up = make_vec3(0.0f, 1.0f, 0.0f);

    Shader_SetInteger(self->shader, "texture_layer0", 0);
    Shader_SetInteger(self->shader, "texture_layer1", 1);
    Shader_SetMatrix4(self->shader, "ProjectionMatrix", &self->camera->ortho_matrix);
    Shader_SetMatrix4(self->shader, "ViewMatrix", &view_matrix);

}

void Renderer_Update(Renderer_t *self)
{
    vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    view_matrix = mat4_lookAt(eye, center, up);
    Shader_SetMatrix4(self->shader, "ViewMatrix", &view_matrix);
    DrawFloorAtPlayer(self, make_vec2(64.0f, 64.0f), 1280.0f, 720.0f);
    //DrawPlayerTile(self, make_vec2(64.0f, 64.0f));
}

void Renderer_ShutDown(Renderer_t *self)
{
    DeleteAllTextures();
    VertexArray_ShutDown(self->vao);
    Shader_ShutDown(self->shader);
    free(self);
}


