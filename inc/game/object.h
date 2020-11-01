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

#ifndef _OBJECT_H_
#define _OBJECT_H_

typedef struct Object_s
{
    Pokemon_t *pokemon;
    // Object state
    bool is_pokemon;
    char  *name;
    vec2   position;
    vec2   size;
    vec2   velocity;
    vec3   color;
    float  rotation;
    bool   solid;
    bool   destroyed;
    // Render state
    Texture_t *sprite;
} Object_t;

Object_t *Object_New(bool is_pokemon, char * object_name, Texture_t * sprite, vec2 position, vec2 size, float rotation, vec3 color);

void Object_Draw(Object_t * self, Renderer_t *renderer);
void Object_UpdateAll(Object_t *self, char *object_name, Texture_t *sprite, vec2 position, vec2 size, float rotation, vec3 color);
void Object_UpdateSprite(Object_t *self, Texture_t *sprite);
void Object_UpdatePosition(Object_t * self, vec2 position);

#endif
