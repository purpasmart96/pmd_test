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

#ifndef _RENDERER2D_MANAGER_H_
#define _RENDERER2D_MANAGER_H_

#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(struct VertexData_s)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

typedef struct Renderer2D_s
{
    struct Camera_s *camera;
    //struct ListRenderer2DInfo *render_queue;
    struct Queue_s *render_queue;
} Renderer2D_t;

typedef struct BatchRenderer2D_s
{
    struct Camera_s *camera;
    //struct Queue_s *render_queue;
    GLuint vao;
    GLuint vbo;
    GLsizei index_count;
    struct IndexBuffer_s *ibo;
    struct VertexData_s *buffer;
} BatchRenderer2D_t;

Renderer2D_t *Renderer2D_New();
void Renderer2D_Init(Renderer2D_t *self);

void Renderer2D_SubmitOld(Renderer2D_t *self, struct Renderer2DInfo_s *element);
void Renderer2D_Submit(Renderer2D_t *self, struct SingleSprite_s *element);
void Renderer2D_Flush(Renderer2D_t *self);
void Renderer2D_Update(Renderer2D_t *self);
void Renderer2D_ShutDown(Renderer2D_t *self);

BatchRenderer2D_t *BatchRenderer2D_New();
void BatchRenderer2D_Init(BatchRenderer2D_t *self);
void BatchRenderer2D_Begin(BatchRenderer2D_t *self);
//void BatchRenderer2D_Submit(BatchRenderer2D_t *self, struct Renderer2DInfo_s *element);
void BatchRenderer2D_Submit(BatchRenderer2D_t *self, struct Sprite_s *element);
void BatchRenderer2D_End(BatchRenderer2D_t *self);
void BatchRenderer2D_Flush(BatchRenderer2D_t *self);
void BatchRenderer2D_Update(BatchRenderer2D_t *self);
void BatchRenderer2D_ShutDown(BatchRenderer2D_t *self);


#endif
