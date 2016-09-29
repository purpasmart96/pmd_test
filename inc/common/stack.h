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


#ifndef _STACK_H_
#define _STACK_H_

#include "util.h"
#include "dungeon/dungeon_gen.h"

#define STACK_DEFUALT 100

typedef struct
{
    void **data;
    int  size;
    size_t  capacity;
} Stack;

Stack *stack_new(size_t capacity);
void stack_resize(Stack *stack, size_t capacity);
void stack_delete(Stack *stack);
bool stack_empty(Stack *stack);
bool stack_full(Stack *stack);
void stack_update(Stack *stack);
void *stack_top(Stack *s);
void *stack_find(Stack *stack, void *element);
void stack_remove(Stack *stack, void *element);
void stack_push(Stack *s, void *element);
void stack_pop(Stack *s);
void stack_clear(Stack *stack);

#endif
