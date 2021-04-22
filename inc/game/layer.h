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

#ifndef _LAYERS_H_
#define _LAYERS_H_

typedef struct Layer_s
{
    Renderer2D_t *renderer;
    struct Queue_s *renderables;
    mat4 *mtx;
    Shader_t *shader;
} Layer_t;

Layer_t *Layer_New(Renderer2D_t *renderer, Shader_t *shader, mat4 *mtx);
void Layer_Init(Layer_t *self, Renderer2D_t *renderer, Shader_t *shader, mat4 *mtx);
void Layer_Add(Layer_t *self, Renderer2DInfo_t *renderable);
void Layer_Draw(Layer_t *self);
void Layer_ShutDown(Layer_t *self);
void Layer_Update(Layer_t *self);

#endif
