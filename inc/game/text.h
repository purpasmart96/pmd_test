// Copyright(c) <2015> <Purpasmart>
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

#ifndef _TEXT_MANAGER_H_
#define _TEXT_MANAGER_H_

#define FLOAT_ARRAY_SIZE 30
#define COLOR_ARRAY_SIZE 40
#define INDICES_ARRAY_SIZE 10
#define UV_ARRAY_SIZE 20

typedef struct TextObject_s {
    char *text;
    float x;
    float y;
    vec4 color;
} TextObject_t;

typedef struct TextManager_s
{
    //private FloatBuffer vertexBuffer;
    //private FloatBuffer textureBuffer;
    //private FloatBuffer colorBuffer;
    //private ShortBuffer drawListBuffer;

    float *vecs;
    float *uvs;
    s16 *indices;
    float *colors;

    int index_vecs;
    int index_indices;
    int index_uvs;
    int index_colors;

    int texturenr;

    float uniform_scale;
    Stack *txt_collection;
} TextManager_t;



#endif
