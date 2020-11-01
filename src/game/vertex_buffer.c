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
#include "common/list_generic.h"

#include "game/vertex_buffer.h"

VertexBuffer_t *VertexBuffer_New(GLfloat *data, GLsizei count, GLuint component_count)
{
    VertexBuffer_t *vertex_buffer = malloc(sizeof(*vertex_buffer));
    if (vertex_buffer)
    {
        VertexBuffer_Init(vertex_buffer, data, count, component_count);
    }
    return vertex_buffer;
}

void VertexBuffer_Init(VertexBuffer_t *self, GLfloat *data, GLsizei count, GLuint component_count)
{
    self->component_count = component_count;

    glGenBuffers(1, &self->buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, self->buffer_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer_Bind(VertexBuffer_t *self)
{
    glBindBuffer(GL_ARRAY_BUFFER, self->buffer_id);
}

void VertexBuffer_Unbind(VertexBuffer_t *self)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer_ShutDown(VertexBuffer_t *self)
{
    glDeleteBuffers(1, &self->buffer_id);
    free(self);
}
