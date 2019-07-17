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

#include "common/dynamic_array.h"

DynamicArray *dynamic_array_new(size_t capacity)
{
    DynamicArray *dynamic_array = malloc(sizeof(*dynamic_array));
    dynamic_array->capacity = capacity;
    dynamic_array->data = malloc(sizeof(TYPE) * dynamic_array->capacity);
    dynamic_array->size = 0;

    dynamic_array->resize = &dynamic_array_resize;
    dynamic_array->empty  = &dynamic_array_empty;
    dynamic_array->full   = &dynamic_array_full;
    //dynamic_array->remove = &dynamic_array_remove;
    dynamic_array->add    = &dynamic_array_add;

    return dynamic_array;
}

TYPE *dynamic_array_resize(DynamicArray *dynamic_array, size_t capacity)
{
    dynamic_array->capacity = capacity;
    TYPE *temp = realloc(dynamic_array->data, sizeof(TYPE) * dynamic_array->capacity);

    if (!temp)
    {
        return NULL;
    }
    dynamic_array->data = temp;

    return temp;
}

void dynamic_array_delete(DynamicArray *dynamic_array)
{
    free(dynamic_array->data);
    free(dynamic_array);
}

bool dynamic_array_empty(DynamicArray *dynamic_array)
{
    return !dynamic_array->size;
}

bool dynamic_array_full(DynamicArray *dynamic_array)
{
    return dynamic_array->size == dynamic_array->capacity;
}

TYPE *dynamic_array_add(DynamicArray *dynamic_array, TYPE element)
{
    if (dynamic_array_full(dynamic_array))
    {
        if (!dynamic_array_resize(dynamic_array, dynamic_array->capacity *= 2))
        { 
            return NULL;
        }
    }

    // Push an element on the top of it and increase its size by one
    dynamic_array->data[dynamic_array->size++] = element;
}

TYPE *dynamic_array_remove_element(DynamicArray *dynamic_array, int index)
{
    TYPE *temp = malloc((dynamic_array->size - 1) * sizeof(TYPE)); // allocate an array with a size 1 less than the current one

    if (index != 0)
        memcpy(temp, dynamic_array->data, (index - 1) * sizeof(TYPE)); // copy everything BEFORE the index

    if (index != (dynamic_array->size - 1))
        memcpy(temp + index, dynamic_array->data + index + 1, (dynamic_array->size - index - 1) * sizeof(TYPE)); // copy everything AFTER the index

    free(dynamic_array->data);
    return temp;
}

