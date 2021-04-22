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
#include "common/list_queue.h"
#include "common/stack.h"
#include "common/rand_num.h"

#include "game/game.h"
#include "game/dungeon.h"
#include "game/sprites.h"
#include "game/player.h"
#include "game/vertex_buffer.h"
#include "game/index_buffer.h"
#include "game/vertex_array.h"
#include "game/camera.h"
#include "game/shader.h"
#include "game/renderer2d_info.h"
#include "game/single_sprite.h"
#include "game/sprite.h"
#include "game/renderer2d.h"


static mat4 *model_matrix;
static mat4 *view_matrix;

static Shader_t *global_shader;

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

#ifdef USE_SLOW_RENDERER
static SingleSprite_t *render_object0;
static SingleSprite_t *render_object1;
static SingleSprite_t *render_object2;
static SingleSprite_t *render_object3;
static SingleSprite_t *render_object4;
static SingleSprite_t *render_object5;
static SingleSprite_t *render_object6;
static SingleSprite_t *render_object7;
static SingleSprite_t *render_object8;
static SingleSprite_t *render_object9;
static SingleSprite_t *render_object10;
static SingleSprite_t *render_object11;
static SingleSprite_t *render_object12;
static SingleSprite_t *render_object13;
static SingleSprite_t *render_object14;
static SingleSprite_t *render_object15;
static SingleSprite_t *render_object16;
static SingleSprite_t *render_object17;
static SingleSprite_t *render_object18;
static SingleSprite_t *render_object19;
#else
static Sprite_t *render_object0;
static Sprite_t *render_object1;
static Sprite_t *render_object2;
static Sprite_t *render_object3;
static Sprite_t *render_object4;
static Sprite_t *render_object5;
static Sprite_t *render_object6;
static Sprite_t *render_object7;
static Sprite_t *render_object8;
static Sprite_t *render_object9;
static Sprite_t *render_object10;
static Sprite_t *render_object11;
static Sprite_t *render_object12;
static Sprite_t *render_object13;
static Sprite_t *render_object14;
static Sprite_t *render_object15;
static Sprite_t *render_object16;
static Sprite_t *render_object17;
static Sprite_t *render_object18;
static Sprite_t *render_object19;
#endif

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

Renderer2D_t *Renderer2D_New()
{
    Renderer2D_t *renderer = malloc(sizeof(*renderer));

    if (renderer)
    {
        Renderer2D_Init(renderer);
    }
    return renderer;
}

void Renderer2D_Submit(Renderer2D_t *self, struct SingleSprite_s *element)
//void Renderer2D_Submit(Renderer2D_t *self, struct Renderer2DInfo_s *element)
{
    //if (!element)
    //    ERROR("NULL element!\n");

    Queue_PushBack(self->render_queue, element);
    //LIST_PUSH(ListRenderer2DInfo, self->render_queue, element);
}

void Renderer2D_SubmitOld(Renderer2D_t *self, struct Renderer2DInfo_s *element)
{
    if (!element)
        ERROR("NULL element!\n");

    Queue_PushBack(self->render_queue, element);
    //LIST_PUSH(ListRenderer2DInfo, self->render_queue, element);
}

void Renderer2D_Flush(Renderer2D_t *self)
{
    while (self->render_queue->size != 0)
    {
        SingleSprite_t *element = self->render_queue->front->data;
        const vec4 color = element->renderer_info->color;

        VertexArray_Bind(element->vertex_array);
        //IndexBuffer_Bind(element->index_buffer);

        mat4 *model = mat4_identity();
        model = mat4_translate(model, element->renderer_info->position.x, element->renderer_info->position.y, 0.0f);
        model = mat4_translate(model, 0.5f * element->renderer_info->size.x, 0.5f * element->renderer_info->size.y, 0.0f);
        //model = mat4_rotate(model, 0.0f, 0.0f, 0.0f, 1.0f);
        model = mat4_translate(model, -0.5f * element->renderer_info->size.x, -0.5f * element->renderer_info->size.y, 0.0f);
        model = mat4_scale_xyz(model, element->renderer_info->size.x, element->renderer_info->size.y, 1.0f);

        const vec3 temp_color = make_vec3(color.r, color.g, color.b);

        Shader_SetMatrix4(element->shader, "ModelMatrix", model);
        Shader_SetVector3f(element->shader, "sprite_color", &temp_color);
        Sprites_BindTexture(element->renderer_info->texture0, 0);
        Sprites_BindTexture(element->renderer_info->texture1, 1);

        //Shader_SetMatrix4(element->shader, "ProjectionMatrix", &self->camera->ortho_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, element->index_buffer->count, GL_UNSIGNED_SHORT, 0);

        //IndexBuffer_Unbind(element->index_buffer);
        VertexArray_Unbind(element->vertex_array);

        SingleSprite_ShutDown(element);

        Queue_PopFront(self->render_queue);
        //LIST_POP_FRONT(ListRenderer2DInfo, self->render_queue);
    }

}

#if defined USE_SLOW_RENDERER || defined USE_FAST_OLD_RENDERER 
static SingleSprite_t *CreateRenderObject(vec3 position, vec2 sprite_size, Texture_t *texture0, Texture_t *texture1)
{
    return SingleSprite_New(make_vec2(position.x, position.y), sprite_size.x, sprite_size.y, make_vec4(1.0f, 1.0f, 1.0f, 1.0f), global_shader, texture0, texture1);
}
#else
static Sprite_t *CreateRenderObject(vec3 position, vec2 sprite_size, Texture_t *texture0, Texture_t *texture1, vec3 color)
{
    return Sprite_New(make_vec2(position.x, position.y), sprite_size.x, sprite_size.y, make_vec4(color.r, color.g, color.b, 1.0f), global_shader, texture0);
}

static Sprite_t *CreateRenderObjectColor(vec3 position, vec2 sprite_size, vec4 color, Texture_t *texture0, Texture_t *texture1)
{
    return Sprite_New(make_vec2(position.x, position.y), sprite_size.x, sprite_size.y, color, global_shader, texture0);
}
#endif

#if defined USE_SLOW_RENDERER || defined USE_FAST_OLD_RENDERER 
static void DrawDungeonSpriteLayers(Renderer2D_t *self, int tile, vec3 position, vec2 sprite_size)
{
    switch (tile)
    {
        case tileUnused:
            render_object0 = CreateRenderObject(position, sprite_size, sprite0, sprite9);
            Renderer2D_Submit(self, render_object0);
            //Renderer2D_Flush(self);
            break;
        case tileEnd:
            render_object1 = CreateRenderObject(position, sprite_size, sprite1, sprite9);
            Renderer2D_Submit(self, render_object1);
            //Renderer2D_Flush(self);
            break;
        case tileWall:
            render_object2 = CreateRenderObject(position, sprite_size, sprite2, sprite9);
            Renderer2D_Submit(self, render_object2);
            //Renderer2D_Flush(self);
            break;
        case tileWallLeft:
            render_object3 = CreateRenderObject(position, sprite_size, sprite3, sprite9);
            Renderer2D_Submit(self, render_object3);
            //Renderer2D_Flush(self);
            break;
        case tileFloor:
            render_object4 = CreateRenderObject(position, sprite_size, sprite4, sprite9);
            Renderer2D_Submit(self, render_object4);
            //Renderer2D_Flush(self);
            break;
        case tileHall:
            render_object5 = CreateRenderObject(position, sprite_size, sprite5, sprite9);
            Renderer2D_Submit(self, render_object5);
            //Renderer2D_Flush(self);
            break;
        case tileStairs:
            render_object6 = CreateRenderObject(position, sprite_size, sprite6, sprite9);
            Renderer2D_Submit(self, render_object6);
            //Renderer2D_Flush(self);
            break;
        case tileLava:
            render_object7 = CreateRenderObject(position, sprite_size, sprite7, sprite9);
            Renderer2D_Submit(self, render_object7);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderUp:
            render_object8 = CreateRenderObject(position, sprite_size, sprite11, sprite9);
            Renderer2D_Submit(self, render_object8);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderRightUp:
            render_object9 = CreateRenderObject(position, sprite_size, sprite12, sprite9);
            Renderer2D_Submit(self, render_object9);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderLeftUp:
            render_object10 = CreateRenderObject(position, sprite_size, sprite10, sprite9);
            Renderer2D_Submit(self, render_object10);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderBottom:
            render_object11 = CreateRenderObject(position, sprite_size, sprite14, sprite9);
            Renderer2D_Submit(self, render_object11);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderBottomRight:
            render_object12 = CreateRenderObject(position, sprite_size, sprite15, sprite9);
            Renderer2D_Submit(self, render_object12);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderBottomLeft:
            render_object13 = CreateRenderObject(position, sprite_size, sprite13, sprite9);
            Renderer2D_Submit(self, render_object13);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderMiddleLeft:
            render_object14 = CreateRenderObject(position, sprite_size, sprite16, sprite9);
            Renderer2D_Submit(self, render_object14);
            //Renderer2D_Flush(self);
            break;
        case tileLavaBorderMiddleRight:
            render_object15 = CreateRenderObject(position, sprite_size, sprite17, sprite9);
            Renderer2D_Submit(self, render_object15);
            //Renderer2D_Flush(self);
            break;
        case tilePlayer:
            render_object16 = CreateRenderObject(position, sprite_size, sprite4, sprite8);
            Renderer2D_Submit(self, render_object16);
            //Renderer2D_Flush(self);
            break;
        default:
            break;
    }
}
#endif

//static void DrawDungeonSpriteLayersBatch(BatchRenderer2D_t *self, int tile, vec3 position, vec2 sprite_size)
//{
//    switch (tile)
//    {
//    case tileUnused:
//        render_object0 = CreateRenderObject(position, sprite_size, sprite0, sprite9);
//        BatchRenderer2D_Submit(self, render_object0->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileEnd:
//        render_object1 = CreateRenderObject(position, sprite_size, sprite1, sprite9);
//        BatchRenderer2D_Submit(self, render_object1->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileWall:
//        render_object2 = CreateRenderObject(position, sprite_size, sprite2, sprite9);
//        BatchRenderer2D_Submit(self, render_object2->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileWallLeft:
//        render_object3 = CreateRenderObject(position, sprite_size, sprite3, sprite9);
//        BatchRenderer2D_Submit(self, render_object3->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileFloor:
//        render_object4 = CreateRenderObject(position, sprite_size, sprite4, sprite9);
//        BatchRenderer2D_Submit(self, render_object4->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileHall:
//        render_object5 = CreateRenderObject(position, sprite_size, sprite5, sprite9);
//        BatchRenderer2D_Submit(self, render_object5->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileStairs:
//        render_object6 = CreateRenderObject(position, sprite_size, sprite6, sprite9);
//        BatchRenderer2D_Submit(self, render_object6->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLava:
//        render_object7 = CreateRenderObject(position, sprite_size, sprite7, sprite9);
//        BatchRenderer2D_Submit(self, render_object7->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderUp:
//        render_object8 = CreateRenderObject(position, sprite_size, sprite11, sprite9);
//        BatchRenderer2D_Submit(self, render_object8->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderRightUp:
//        render_object9 = CreateRenderObject(position, sprite_size, sprite12, sprite9);
//        BatchRenderer2D_Submit(self, render_object9->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderLeftUp:
//        render_object10 = CreateRenderObject(position, sprite_size, sprite10, sprite9);
//        BatchRenderer2D_Submit(self, render_object10->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderBottom:
//        render_object11 = CreateRenderObject(position, sprite_size, sprite14, sprite9);
//        BatchRenderer2D_Submit(self, render_object11->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderBottomRight:
//        render_object12 = CreateRenderObject(position, sprite_size, sprite15, sprite9);
//        BatchRenderer2D_Submit(self, render_object12->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderBottomLeft:
//        render_object13 = CreateRenderObject(position, sprite_size, sprite13, sprite9);
//        BatchRenderer2D_Submit(self, render_object13->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderMiddleLeft:
//        render_object14 = CreateRenderObject(position, sprite_size, sprite16, sprite9);
//        BatchRenderer2D_Submit(self, render_object14->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tileLavaBorderMiddleRight:
//        render_object15 = CreateRenderObject(position, sprite_size, sprite17, sprite9);
//        BatchRenderer2D_Submit(self, render_object15->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    case tilePlayer:
//        render_object16 = CreateRenderObject(position, sprite_size, sprite4, sprite8);
//        BatchRenderer2D_Submit(self, render_object16->renderer_info);
//        //Renderer2D_Flush(self);
//        break;
//    default:
//        break;
//    }
//}

static tid = 0;

static void DrawDungeonSpriteLayersBatch(BatchRenderer2D_t *self, int tile, vec3 position, vec2 sprite_size)
{
    switch (tile)
    {
    case tileUnused:
        render_object0 = CreateRenderObject(position, sprite_size, sprite0, sprite9, make_vec3(0.3, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object0);
        //Renderer2D_Flush(self);
        break;
    case tileEnd:
        render_object1 = CreateRenderObject(position, sprite_size, sprite1, sprite9, make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object1);
        //Renderer2D_Flush(self);
        break;
    case tileWall:
        render_object2 = CreateRenderObject(position, sprite_size, sprite2, sprite9, make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object2);
        //Renderer2D_Flush(self);
        break;
    case tileWallLeft:
        render_object3 = CreateRenderObject(position, sprite_size, sprite3, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object3);
        //Renderer2D_Flush(self);
        break;
    case tileFloor:
        render_object4 = CreateRenderObject(position, sprite_size, sprite4, sprite9, make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object4);
        //Renderer2D_Flush(self);
        break;
    case tileHall:
        render_object5 = CreateRenderObject(position, sprite_size, sprite5, sprite9,make_vec3(0.4, 0.8, 0.9));
        BatchRenderer2D_Submit(self, render_object5);
        //Renderer2D_Flush(self);
        break;
    case tileStairs:
        render_object6 = CreateRenderObject(position, sprite_size, sprite6, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object6);
        //Renderer2D_Flush(self);
        break;
    case tileLava:
        render_object7 = CreateRenderObject(position, sprite_size, sprite7, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object7);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderUp:
        render_object8 = CreateRenderObject(position, sprite_size, sprite11, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object8);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderRightUp:
        render_object9 = CreateRenderObject(position, sprite_size, sprite12, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object9);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderLeftUp:
        render_object10 = CreateRenderObject(position, sprite_size, sprite10, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object10);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderBottom:
        render_object11 = CreateRenderObject(position, sprite_size, sprite14, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object11);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderBottomRight:
        render_object12 = CreateRenderObject(position, sprite_size, sprite15, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object12);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderBottomLeft:
        render_object13 = CreateRenderObject(position, sprite_size, sprite13, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object13);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderMiddleLeft:
        render_object14 = CreateRenderObject(position, sprite_size, sprite16, sprite9,make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object14);
        //Renderer2D_Flush(self);
        break;
    case tileLavaBorderMiddleRight:
        render_object15 = CreateRenderObject(position, sprite_size, sprite17, sprite9, make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object15);
        //Renderer2D_Flush(self);
        break;
    case tilePlayer:
        render_object16 = CreateRenderObject(position, sprite_size, sprite4, sprite8, make_vec3(1.0, 1.0, 1.0));
        BatchRenderer2D_Submit(self, render_object16);
        //Renderer2D_Flush(self);
        break;
    default:
        break;
    }
}

static void DrawFloorAtPlayer(Renderer2D_t *renderer, vec2 sprite_size, float width, float height, ivec2 position)
{
    //ivec2 position = Player_GetPosition(GetPlayerInstance());

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
                    #ifndef USE_BATCH_RENDERER
                    DrawDungeonSpriteLayers(renderer, tileUnused, make_vec3(coord_x, coord_y, 0.0f), sprite_size);
                    #endif
                }
                else
                {
                    #ifndef USE_BATCH_RENDERER
                    DrawDungeonSpriteLayers(renderer, dungeon->floor->tiles[new_coord_x][new_coord_y].tile, make_vec3(coord_x, coord_y, 0.0f), sprite_size);
                    #endif
                }

            }
            else if (!is_coord_x_inside && !is_coord_y_inside)
            {
                return;
            }
        }
    }

}

static void DrawFloorAtPlayerBatch(BatchRenderer2D_t *renderer, vec2 sprite_size, float width, float height, vec2 position)
{
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
                    DrawDungeonSpriteLayersBatch(renderer, tileUnused, make_vec3(coord_x, coord_y, 0.0f), sprite_size);
                }
                else
                {
                    DrawDungeonSpriteLayersBatch(renderer, dungeon->floor->tiles[new_coord_x][new_coord_y].tile, make_vec3(coord_x, coord_y, 0.0f), sprite_size);
                }

            }
            else if (!is_coord_x_inside && !is_coord_y_inside)
            {
                return;
            }
        }
    }

}

void Renderer2D_Init(Renderer2D_t *self)
{
    //self->render_queue = LIST_NEW(ListRenderer2DInfo);
    self->render_queue = Queue_New();
    global_shader = Shader_New("data/shaders/sprite_slow.vsh", "data/shaders/sprite_slow.psh");

    LoadAllTextures();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    self->camera = Camera_New(eye, center, up, 1280.0f, 720.0f);

    view_matrix = mat4_identity();
    //ortho_matrix = mat4_ortho(ortho_matrix, 0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    //vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    //vec3 center = make_vec3(1.0f, 1.0f, 0.0f);
    //vec3 up = make_vec3(0.0f, 1.0f, 0.0f);

    Shader_SetInteger(global_shader, "texture_layer0", 0);
    Shader_SetInteger(global_shader, "texture_layer1", 1);
    Shader_SetMatrix4(global_shader, "ProjectionMatrix", self->camera->ortho_matrix);
    Shader_SetMatrix4(global_shader, "ViewMatrix", view_matrix);
}

void Renderer2D_Update(Renderer2D_t *self, ivec2 position)
{
    //vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    //vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    //vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    //view_matrix = mat4_lookAt(eye, center, up);

    
    //DrawDungeonSpriteLayers(self, tileUnused, make_vec3(0.0f, 0.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(64.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(128.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));

    DrawFloorAtPlayer(self, make_vec2(64.0f, 64.0f), 1280.0f, 720.0f, position);
    Renderer2D_Flush(self);
    //_CrtDumpMemoryLeaks();
}

void Renderer2D_ShutDown(Renderer2D_t *self)
{
    DeleteAllTextures();
    Shader_ShutDown(global_shader);
    Queue_ShutDown(self->render_queue);
    Camera_ShutDown(self->camera);
    //LIST_DELETE(ListRenderer2DInfo, self->render_queue);
    free(self);
}

BatchRenderer2D_t *BatchRenderer2D_New()
{
    BatchRenderer2D_t *renderer = malloc(sizeof(*renderer));

    if (renderer)
    {
        BatchRenderer2D_Init(renderer);
    }
    return renderer;
}

static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                       GLenum severity, GLsizei length, 
                                       const GLchar *message, const void *userParam)
{
    ERROR("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
         (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
         type, severity, message);
}

void BatchRenderer2D_Init(BatchRenderer2D_t *self)
{
    //self->render_queue = Queue_New();
    self->index_count = 0;
    global_shader = Shader_New("data/shaders/sprite_batch.vsh", "data/shaders/sprite_batch.psh");

    LoadAllTextures();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    //glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    vec3 center = make_vec3(0.0f, 0.0f, -1.0f);
    vec3 up = make_vec3(0.0f, 1.0f, 0.0f);
    self->camera = Camera_New(eye, center, up, 1920.0f, 1080.0f);
    //self->camera = Camera_New(eye, center, up, 1280.0f, 720.0f);

    view_matrix = mat4_identity();

    model_matrix = mat4_identity();
    //model = mat4_translate(model, element->position.x, element->position.y, 0.0f);
    //model = mat4_translate(model, 0.5f * element->size.x, 0.5f * element->size.y, 0.0f);
    //model = mat4_rotate(model, 0.0f, 0.0f, 0.0f, 1.0f);
    //model = mat4_translate(model, -0.5f * element->size.x, -0.5f * element->size.y, 0.0f);
    //model = mat4_scale_xyz(model, element->size.x, element->size.y, 1.0f);


    //ortho_matrix = mat4_ortho(ortho_matrix, 0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    //vec3 eye = make_vec3(0.0f, 0.0f, 0.0f);
    //vec3 center = make_vec3(1.0f, 1.0f, 0.0f);
    //vec3 up = make_vec3(0.0f, 1.0f, 0.0f);

    Shader_SetInteger(global_shader, "texture_layer0", 0);
    Shader_SetInteger(global_shader, "texture_layer1", 1);
    Shader_SetMatrix4(global_shader, "ProjectionMatrix", self->camera->ortho_matrix);
    Shader_SetMatrix4(global_shader, "ViewMatrix", view_matrix);
    Shader_SetMatrix4(global_shader, "ModelMatrix", model_matrix);

    const int vertex_index = 0;
    const int color_index = 1;
    const int texcoord_index = 2;

    glGenVertexArrays(1, &self->vao);
    glGenBuffers(1, &self->vbo);

    glBindVertexArray(self->vao);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(vertex_index);
    glEnableVertexAttribArray(color_index);
    glEnableVertexAttribArray(texcoord_index);
    glVertexAttribPointer(vertex_index,   3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)offsetof(VertexData_t, vertex));
    glVertexAttribPointer(color_index,    4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (GLvoid*)offsetof(VertexData_t, color));
    glVertexAttribPointer(texcoord_index, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)offsetof(VertexData_t, texcoord));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //GLushort indices[RENDERER_INDICES_SIZE];
    GLuint *indices = malloc(sizeof(GLuint) * RENDERER_INDICES_SIZE);
    //GLushort *indices = malloc(sizeof(GLushort) * RENDERER_INDICES_SIZE);

    int offset = 0;
    for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
    {
        indices[i] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }

    self->ibo = IndexBuffer_New(indices, RENDERER_INDICES_SIZE);
    glBindVertexArray(0);
}

void BatchRenderer2D_Begin(BatchRenderer2D_t *self)
{
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);

    self->buffer = (struct VertexData_s*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    GLenum error = glGetError();
    if (error != GL_FALSE)
    {
        ERROR("%i\n", error);
    }
}

//void BatchRenderer2D_Submit(BatchRenderer2D_t * self, struct Renderer2DInfo_s *element)
//{
//    const vec3 position = element->position;
//    const vec4 color = element->color;
//    const vec2 size = element->size;
//    const vec2 *texcoords = element->texcoords;
//
//    //mat4 model = mat4_identity();
//    //model = mat4_translate(model, element->position.x, element->position.y, 0.0f);
//    //model = mat4_translate(model, 0.5f * element->size.x, 0.5f * element->size.y, 0.0f);
//    //model = mat4_rotate(model, 0.0f, 0.0f, 0.0f, 1.0f);
//    //model = mat4_translate(model, -0.5f * element->size.x, -0.5f * element->size.y, 0.0f);
//    //model = mat4_scale_xyz(model, element->size.x, element->size.y, 1.0f);
//
//    //Shader_SetMatrix4(global_shader, "ModelMatrix", &model);
//    Shader_SetVector3f(global_shader, "sprite_color", &color);
//    Sprites_BindTexture(element->texture0, 0);
//    //Sprites_BindTexture(element->texture1, 1);
//
//    self->buffer->vertex = position;
//    self->buffer->color = color;
//    self->buffer->texcoord = texcoords[0];
//    self->buffer++;
//
//    self->buffer->vertex = make_vec3(position.x, position.y + size.y, position.z);
//    self->buffer->color = color;
//    self->buffer->texcoord = texcoords[1];
//    self->buffer++;
//
//    self->buffer->vertex = make_vec3(position.x + size.x, position.y + size.y, position.z);
//    self->buffer->color = color;
//    self->buffer->texcoord = texcoords[2];
//    self->buffer++;
//
//    self->buffer->vertex = make_vec3(position.x + size.x, position.y, position.z);
//    self->buffer->color = color;
//    self->buffer->texcoord = texcoords[3];
//    self->buffer++;
//
//    self->index_count += 6;
//}

void BatchRenderer2D_Submit(BatchRenderer2D_t * self, struct Sprite_s *element)
{
    const vec3 position = element->renderer_info->position;
    const vec4 color = element->renderer_info->color;
    const vec2 size = element->renderer_info->size;
    const vec2 *texcoords = element->renderer_info->texcoords;

    int r = color.r * 255.0f;
    int g = color.g * 255.0f;
    int b = color.b * 255.0f;
    int a = color.a * 255.0f;

    u32 new_color = a << 24 | b << 16 | g << 8 | r;

    //mat4 model = mat4_identity();
    //model = mat4_translate(model, element->position.x, element->position.y, 0.0f);
    //model = mat4_translate(model, 0.5f * element->size.x, 0.5f * element->size.y, 0.0f);
    //model = mat4_rotate(model, 0.0f, 0.0f, 0.0f, 1.0f);
    //model = mat4_translate(model, -0.5f * element->size.x, -0.5f * element->size.y, 0.0f);
    //model = mat4_scale_xyz(model, element->size.x, element->size.y, 1.0f);

    //Shader_SetMatrix4(global_shader, "ModelMatrix", &model);
    //const vec3 temp_color = make_vec3(color.r, color.g, color.b);
    //Shader_SetVector4f(element->shader, "sprite_color", &color);
    Sprites_BindTexture(element->renderer_info->texture0, 0);
    //Sprites_BindTexture(element->texture1, 1);

    self->buffer->vertex = position;
    self->buffer->color = new_color;
    self->buffer->texcoord = texcoords[0];
    self->buffer++;

    self->buffer->vertex = make_vec3(position.x, position.y + size.y, position.z);
    self->buffer->color = new_color;
    self->buffer->texcoord = texcoords[1];
    self->buffer++;

    self->buffer->vertex = make_vec3(position.x + size.x, position.y + size.y, position.z);
    self->buffer->color = new_color;
    self->buffer->texcoord = texcoords[2];
    self->buffer++;

    self->buffer->vertex = make_vec3(position.x + size.x, position.y, position.z);
    self->buffer->color = new_color;
    self->buffer->texcoord = texcoords[3];
    self->buffer++;

    self->index_count += 6;

    Sprite_ShutDown(element);
}

void BatchRenderer2D_End(BatchRenderer2D_t *self)
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchRenderer2D_Flush(BatchRenderer2D_t *self)
{
    glBindVertexArray(self->vao);
    IndexBuffer_Bind(self->ibo);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, self->index_count, GL_UNSIGNED_INT, NULL);

    IndexBuffer_Unbind(self->ibo);
    glBindVertexArray(0);

    self->index_count = 0;
}

void BatchRenderer2D_Update(BatchRenderer2D_t *self, vec2 position)
{
    BatchRenderer2D_Begin(self);

    //DrawDungeonSpriteLayersBatch(self, tileWall, make_vec3(128.0f, 0.0f, 0.0f), make_vec2(64.0f, 64.0f));
    DrawFloorAtPlayerBatch(self, make_vec2(64.0f, 64.0f), 1920.0f, 1080.0f, position);

    //for (float i = 0.0f; i < 1280.0f; i += 128.f)
    //{
    //    //Renderer_DrawSprite(self, LoadTexture("stairs_desc.png"), make_vec2(64.0f, 64.0f), make_vec2(64.0f, 64.0f), 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
    //    //Renderer_DrawSprite(self, LoadTexture("dirt.png"), make_vec2(128.0f, 64.0f), make_vec2(64.0f, 64.0f), 0.0f, make_vec3(1.0f, 1.0f, 1.0f));
    //    float tile_one_pos = i - 64.0f;
    //    float tile_two_pos = i;
    //    if (i == 0)
    //    {
    //        tile_one_pos = 0.0f;
    //        tile_two_pos = 64.0f;
    //    }

    //    render_object2 = CreateRenderObjectColor(make_vec3(tile_one_pos, 64.0f, 0.0f), make_vec2(64.0f, 64.0f), make_vec4(0.3f, 0.4f, 0.7f, 1.0f), sprite2, sprite9);
    //    BatchRenderer2D_Submit(self, render_object2);
    //    //render_object4 = CreateRenderObjectColor(make_vec3(tile_two_pos, 64.0f, 0.0f), make_vec2(64.0f, 64.0f), make_vec4(0.5f, 0.7f, 0.3f, 1.0f), sprite4, sprite9);
    //    //BatchRenderer2D_Submit(self, render_object4);
    //    //DrawDungeonSpriteLayersBatch(self, tileFloor, make_vec3(tile_one_pos, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //    //DrawDungeonSpriteLayersBatch(self, tileLava, make_vec3(tile_two_pos, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //}


    //DrawDungeonSpriteLayersBatch(self, tileWall, make_vec3(0.0f, 0.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayersBatch(self, tileFloor, make_vec3(64.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayersBatch(self, tileUnused, make_vec3(128.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));

    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(64.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(128.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));

    BatchRenderer2D_End(self);
    BatchRenderer2D_Flush(self);

    //DrawDungeonSpriteLayers(self, tileUnused, make_vec3(0.0f, 0.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(64.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
    //DrawDungeonSpriteLayers(self, tileFloor, make_vec3(128.0f, 64.0f, 0.0f), make_vec2(64.0f, 64.0f));
}

void BatchRenderer2D_ShutDown(BatchRenderer2D_t * self)
{
    IndexBuffer_ShutDown(self->ibo);
    glDeleteBuffers(1, &self->vbo);

    free(model_matrix);
    free(view_matrix);
}

