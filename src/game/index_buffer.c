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

#include "game/index_buffer.h"

IndexBuffer_t *IndexBuffer_New(GLuint *data, GLsizei count)
{
    IndexBuffer_t *index_buffer = malloc(sizeof(*index_buffer));
    if (index_buffer)
    {
        IndexBuffer_Init(index_buffer, data, count);
    }
    return index_buffer;
}

void IndexBuffer_Init(IndexBuffer_t *self, GLuint *data, GLsizei count)
{
    self->count = count;

    glGenBuffers(1, &self->buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer_Bind(IndexBuffer_t *self)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->buffer_id);
}

void IndexBuffer_Unbind(IndexBuffer_t *self)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer_ShutDown(IndexBuffer_t *self)
{
    glDeleteBuffers(1, &self->buffer_id);
    free(self);
}
