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


#include "common\stack.h"


StackRect *stack_rect_new()
{
    StackRect *stack = (StackRect*)calloc(0, sizeof(Stack));
    stack->capacity = STACK_MAX;
    stack->data = malloc(sizeof(Rect) * stack->capacity);
    stack->size = 0;
    return stack;
}

Stack *stack_new()
{
    Stack *stack = (Stack*)calloc(0, sizeof(Stack));
    stack->capacity = STACK_MAX;
    stack->data = malloc(sizeof(u32) * stack->capacity);
    stack->size = 0;
    return stack;
}

void delete_stack(Stack *stack)
{
    free(stack->data);
    free(stack);
}

void stack_init(Stack *s)
{
    // Initialise its properties
    s->capacity = STACK_MAX;
    s->data = (u32*)malloc(sizeof(u32) * s->capacity);
    s->size = 0;
}

void stack_static_init(Stack *s, int capacity)
{
    s->capacity = capacity;
    s->data = (u32*)malloc(sizeof(u32) * s->capacity);
    s->size = 0;
}

void stack_static_init_size(Stack *s, int capacity, int size)
{
    s->capacity = capacity;
    s->data = (u32*)malloc(sizeof(u32) * s->capacity);
    s->size = size;
}

bool empty(Stack *s)
{
    if (s->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int top(Stack *s)
{
    if (s->size == 0)
    {
        ERROR("Stack is Empty\n");
    }
    // Return the topmost element
    return s->data[s->size - 1];
}

void push(Stack *s, int element)
{
    // If the stack is full, we cannot push an element into it as there is no space for it.
    if (s->size == s->capacity)
    {
        ERROR("Stack is Full\n");
    }
    else
    {
        // Push an element on the top of it and increase its size by one
        s->data[s->size++] = element;
    }
    return;
}

void pop_back(Stack *s)
{
    // If stack size is zero then it is empty. So we cannot pop
    if (s->size == 0)
    {
        ERROR("Stack is Empty\n");
        return;
    }
    // Removing an element is equivalent to reducing its size by one
    else
    {
        s->size--;
    }
    return;
}

void clear(Stack *s)
{
    while (!empty(s))
    {
        pop_back(s);
    }
    return;
}
