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

#include "common/list_types.h"

#if defined(NODE_T)
#include "common/template.h"

NODE_T *TEMPLATE(node_new, NODE_T)(T data)
{
    NODE_T *node = (NODE_T*) malloc(sizeof(*node));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;
    return node;
}

#else

#define NODE_T ListNodeChar
#define T char
#include "node_generic.c"
#undef T
#undef NODE_T

#define NODE_T ListNodeInt
#define T int
#include "node_generic.c"
#undef T
#undef NODE_T

#define NODE_T ListNodeCharPtr
#define T u8 *
#include "node_generic.c"
#undef T
#undef NODE_T

#define NODE_T ListNodeTexture
#define T Texture_t
#include "node_generic.c"
#undef T
#undef NODE_T

#endif
