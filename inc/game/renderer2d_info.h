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


#ifndef _RENDERER2D_INFO_MANAGER_H_
#define _RENDERER2D_INFO_MANAGER_H_

typedef struct VertexData_s
{
    vec3 vertex;
    u32  color;
    vec2 texcoord;
} VertexData_t;

typedef struct Renderer2DInfo_s
{
    vec3 position;
    vec2 size;
    vec4 color;
    vec2 texcoords[4];

    Texture_t *texture0;
    Texture_t *texture1;

} Renderer2DInfo_t;

Renderer2DInfo_t *Renderer2DInfo_New(vec3 position, vec2 size, vec4 color, Texture_t *texture0, Texture_t *texture1);
void Renderer2DInfo_Init(Renderer2DInfo_t *self, vec3 position, vec2 size, vec4 color, Texture_t *texture0, Texture_t *texture1);
void Renderer2DInfo_ShutDown(Renderer2DInfo_t *self);

//void Renderer_InitRenderData(Renderer_t *self);

//void DrawSprite(Renderer_t *self, vec2 position, vec2 size, GLfloat rotate, vec4 color);

#endif
