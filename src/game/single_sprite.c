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

#include "game/vertex_buffer.h"
#include "game/index_buffer.h"
#include "game/vertex_array.h"
#include "game/camera.h"
#include "game/shader.h"
#include "game/renderer2d_info.h"
#include "game/sprites.h"
#include "game/single_sprite.h"
#include "game/renderer2d.h"

static GLfloat texcoords[] =
{
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

GLfloat vertices[] = {
    // Pos  
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

static GLushort indices[] =
{
    0,1,2, // first triangle (bottom left - top left - top right)
    2,3,0 // second triangle (bottom left - top right - bottom right)
};

SingleSprite_t *SingleSprite_New(vec2 position, float width, float height, vec4 color, struct Shader_s *shader, struct Texture_s *texture0, struct Texture_s *texture1)
{
    SingleSprite_t *sprite = malloc(sizeof(*sprite));

    if (sprite)
    {
        SingleSprite_Init(sprite, position, width, height, color, shader, texture0, texture1);
    }
    return sprite;
}

void SingleSprite_Init(SingleSprite_t *self, vec2 position, float width, float height, vec4 color, struct Shader_s *shader, struct Texture_s *texture0, struct Texture_s *texture1)
{
    self->renderer_info = Renderer2DInfo_New(make_vec3(position.x, position.y, 0.0f), make_vec2(width, height), color, texture0, texture1);
    self->shader = shader;
    self->vertex_array = VertexArray_New();
    
    //GLfloat vertices[] = {
    //    0, 0, 0,
    //    0, height, 0,
    //    width, height, 0,
    //    width, 0, 0
    //};

    GLfloat colors[] = {
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a
    };

    VertexBuffer_t *vbo_vertices = VertexBuffer_New(vertices, 6 * 2, 2);
    //VertexBuffer_t *vbo_vertices  = VertexBuffer_New(vertices, 4 * 3, 3);
    VertexBuffer_t *vbo_colors    = VertexBuffer_New(colors, 4 * 4, 4);
    VertexBuffer_t *vbo_texcoords = VertexBuffer_New(texcoords, 6 * 2, 2);

    const GLuint vertex_index = 0;
    const GLuint color_index = 1;
    const GLuint texcoords_index = 2;

    VertexArray_AddBuffer(self->vertex_array, vbo_vertices, vertex_index);
    VertexArray_AddBuffer(self->vertex_array, vbo_colors, color_index);
    VertexArray_AddBuffer(self->vertex_array, vbo_texcoords, texcoords_index);

    //self->index_buffer = IndexBuffer_New(indices, 6);
}

void SingleSprite_ShutDown(SingleSprite_t *self)
{
    Renderer2DInfo_ShutDown(self->renderer_info);
    //IndexBuffer_ShutDown(self->index_buffer);
    VertexArray_ShutDown(self->vertex_array);
    free(self);
}