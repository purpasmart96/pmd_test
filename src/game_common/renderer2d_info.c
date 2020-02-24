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

#include "game_common/vertex_buffer.h"
#include "game_common/index_buffer.h"
#include "game_common/vertex_array.h"
#include "game_common/camera.h"
#include "game_common/shader.h"
#include "game_common/renderer2d_info.h"


Renderer2DInfo_t *Renderer2DInfo_New(vec3 position, vec2 size, vec4 color, Texture_t *texture0, Texture_t *texture1)
{
    Renderer2DInfo_t *renderer = malloc(sizeof(*renderer));

    if (renderer)
    {
        Renderer2DInfo_Init(renderer, position, size, color, texture0, texture1);
    }

    return renderer;
}

void Renderer2DInfo_Init(Renderer2DInfo_t *self, vec3 position, vec2 size, vec4 color, Texture_t *texture0, Texture_t *texture1)
{
    self->position = position;
    self->size = size;
    self->color = color;

    self->texcoords[0] = make_vec2(0.0f, 0.0f);
    self->texcoords[1] = make_vec2(0.0f, 1.0f);
    self->texcoords[2] = make_vec2(1.0f, 1.0f);
    self->texcoords[3] = make_vec2(1.0f, 0.0f);

    self->texture0 = texture0;
    self->texture1 = texture1;
}

void Renderer2DInfo_ShutDown(Renderer2DInfo_t *self)
{
    //free(self->texture1);
    //free(self->texture0);
    //VertexArray_ShutDown(self->vertex_array);
    //IndexBuffer_ShutDown(self->index_buffer);
    free(self);
}
