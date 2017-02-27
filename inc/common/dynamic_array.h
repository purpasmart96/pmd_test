// Copyright(c) 2015 Purpasmart
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


#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include "util.h"

#define STACK_DEFUALT 100

typedef struct TYPE
{
    enum
    {
        TypeUndefined,
        TypeS32,           // 1
        TypeU32,
        TypeString,
        TypeU64,
    } Type;

    union
    {
        s32 int_t;
        u32 u32_t;
        char *string;
        u64 u64_t;
    };
} TYPE;

typedef struct DynamicArray_s
{
    TYPE *data;
    size_t  size;
    size_t  capacity;

    TYPE (*resize)(struct DynamicArray_s *, size_t);
    bool (*empty)(struct DynamicArray_s *);
    bool (*full)(struct DynamicArray_s *);
    TYPE (*remove)(struct DynamicArray_s *, int);
    TYPE *(*add)(struct DynamicArray_s *, TYPE);
} DynamicArray;

DynamicArray *dynamic_array_new(size_t capacity);
TYPE *dynamic_array_resize(DynamicArray *dynamic_array, size_t capacity);
void dynamic_array_delete(DynamicArray *dynamic_array);
bool dynamic_array_empty(DynamicArray *dynamic_array);
bool dynamic_array_full(DynamicArray *dynamic_array);
void dynamic_array_update(DynamicArray *dynamic_array);
void *dynamic_array_top(DynamicArray *dynamic_array);
void *dynamic_array_find(DynamicArray *dynamic_array, void *element);
void dynamic_array_remove(DynamicArray *dynamic_array, void *element);
TYPE *dynamic_array_add(DynamicArray *dynamic_array, TYPE element);
TYPE *dynamic_array_remove_element(DynamicArray *dynamic_array, int index);

#endif
