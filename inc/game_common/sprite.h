// Copyright(c) 2017 Purpasmart
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

#ifndef _SPRITE23_H_
#define _SPRITE23_H_

typedef struct Sprite_s
{
    struct Renderer2DInfo_s *renderer_info;
    //struct VertexArray_s *vertex_array;
    //struct IndexBuffer_s *index_buffer;
    struct Shader_s *shader;
} Sprite_t;


Sprite_t *Sprite_New(vec2 position, float width, float height, vec4 color, struct Shader_s *shader, struct Texture_s *texture);
void Sprite_ShutDown(Sprite_t *self);

void Sprite_Init(Sprite_t *self, vec2 size, float width, float height, vec4 color, struct Shader_s *shader, struct Texture_s *texture);

#endif
