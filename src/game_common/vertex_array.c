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

#include "util.h"

#include <GL/glew.h>
#include <glfw3.h>

#include "common/vec.h"
//#include "common/list_generic.h"
#include "common/stack.h"

#include "game_common/vertex_buffer.h"
#include "game_common/vertex_array.h"


VertexArray_t *VertexArray_New()
{
    VertexArray_t *vertex_array = malloc(sizeof(*vertex_array));
    if (vertex_array)
    {
        VertexArray_Init(vertex_array);
    }
    return vertex_array;
}

void VertexArray_Init(VertexArray_t *self)
{
    self->vertex_buffers = stack_new(10);
    glGenVertexArrays(1, &self->array_id);
}

void VertexArray_AddBuffer(VertexArray_t *self, VertexBuffer_t *vertex_buffer, GLuint index)
{
    VertexArray_Bind(self);
    VertexBuffer_Bind(vertex_buffer);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vertex_buffer->component_count, GL_FLOAT, GL_FALSE, 0, 0);

    stack_push(self->vertex_buffers, vertex_buffer);
    VertexBuffer_Unbind(vertex_buffer);
    VertexArray_Unbind(self);
}

void VertexArray_Bind(VertexArray_t *self)
{
    glBindVertexArray(self->array_id);
}

void VertexArray_Unbind(VertexArray_t *self)
{
    glBindVertexArray(0);
}

void VertexArray_ShutDown(VertexArray_t *self)
{
    for (int i = 0; i < self->vertex_buffers->size; i++)
    {
        VertexBuffer_ShutDown(self->vertex_buffers->data[i]);
        //free(self->vertex_buffers->data[i]);
    }

    stack_delete(self->vertex_buffers);
    glDeleteVertexArrays(1, &self->array_id);
    free(self);
}

