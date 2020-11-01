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


#ifndef _RENDERER_MANAGER_H_
#define _RENDERER_MANAGER_H_

#include <pthread.h>

typedef struct Renderer_s
{
    bool renderering;
    pthread_mutex_t mutex;
    pthread_t thread_id;
    struct Camera_s *camera;
    struct Shader_s *shader;
    struct VertexArray_s *vao;
    //struct VertexBuffer_s *vbo;
    struct IndexBuffer_s *ibo;
    mat4   model_matrix;
    GLint image_sampler;
    mat4 view_matrix;
} Renderer_t;

Renderer_t *Renderer_New(bool init);
void Renderer_DrawSprite(Renderer_t *self, Texture_t *texture, vec2 position, vec2 size, GLfloat rotate, vec3 color);

void Renderer_Init(Renderer_t *self);
void Renderer_StartThread(Renderer_t *self);
//void DrawDungeonSprite(Renderer_t * self, Tile tile, vec2 position);
void Renderer_Update(Renderer_t *self, ivec2 position);
void Renderer_ShutDown(Renderer_t *self);


//void Renderer_InitRenderData(Renderer_t *self);

//void DrawSprite(Renderer_t *self, vec2 position, vec2 size, GLfloat rotate, vec4 color);

#endif
