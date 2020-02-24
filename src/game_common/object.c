// Copyright(c) 2020 Purpasmart
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

#include <GL/glew.h>
#include <glfw3.h>

#include "common/vec.h"
#include "common/list_generic.h"

#include "game_common/move.h"
#include "game_common/pokemon.h"
#include "game_common/sprites.h"
#include "game_common/renderer.h"
#include "game_common/object.h"


Object_t *Object_New(bool is_pokemon, char *object_name, Texture_t *sprite, vec2 position, vec2 size, float rotation, vec3 color)
{
    if (is_pokemon)
    {
        return NULL;
    }
    else
    {
        Object_t *object = malloc(sizeof(*object));
        object->is_pokemon = false;
        object->pokemon = NULL;
        strlcpy(object->name, object_name, sizeof(object->name));
        //object->name = object_name;
        object->sprite = sprite;
        object->position = position;
        object->size = size;
        object->rotation = rotation;
        object->solid = false;
        object->destroyed = false;
        //LoadTexture("dirt.png"), make_vec2(128.0f, 64.0f), make_vec2(64.0f, 64.0f), 0.0f, make_vec3(1.0f, 1.0f, 1.0f)
        return object;
    }
}

void Object_Draw(Object_t *self, Renderer_t *renderer)
{
    Renderer_DrawSprite(renderer, self->sprite, self->position, self->size, self->rotation, self->color);
}

void Object_UpdateAll(Object_t *self, char *object_name, Texture_t *sprite, vec2 position, vec2 size, float rotation, vec3 color)
{
    strlcpy(self->name, object_name, sizeof(self->name));
    //object->name = object_name;
    self->sprite = sprite;
    self->position = position;
    self->size = size;
    self->rotation = rotation;
    self->solid = false;
    self->destroyed = false;
    //LoadTexture("dirt.png"), make_vec2(128.0f, 64.0f), make_vec2(64.0f, 64.0f), 0.0f, make_vec3(1.0f, 1.0f, 1.0f)
}

void Object_UpdateSprite(Object_t *self, Texture_t *sprite)
{
    self->sprite = sprite;
}

void Object_UpdatePosition(Object_t *self, vec2 position)
{
    self->position = position;
}