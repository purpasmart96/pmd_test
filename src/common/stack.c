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


#include "common/stack.h"


Stack *stack_new(size_t capacity)
{
    Stack *stack = malloc(sizeof(*stack));
    stack->capacity = capacity;
    stack->data = malloc(sizeof(void *) * stack->capacity);
    stack->size = 0;
    return stack;
}

void *stack_resize(Stack *stack, size_t capacity)
{
    stack->capacity = capacity;
    void **temp = realloc(stack->data, sizeof(void *) * stack->capacity);

    if (!temp)
    {
        return NULL;
    }
    stack->data = temp;
}

void stack_delete(Stack *stack)
{
    free(stack->data);
    free(stack);
}

bool stack_empty(Stack *stack)
{
    return !stack->size;
}

bool stack_full(Stack *stack)
{
    return stack->size == stack->capacity;
}

void stack_update(Stack *stack)
{
    Stack *stack_temp = stack_new(stack->capacity);

    for (size_t i = 0; i < stack->size; i++)
    {
        if (stack->data[i] != NULL) // Find a non-empty slot
        {
            stack_push(stack_temp, stack->data[i]);
        }
    }

    memcpy(stack, stack_temp, sizeof(stack));
    stack_delete(stack_temp);
}

void *stack_top(Stack *stack)
{
    if (stack_empty(stack))
    {
        ERROR("Stack is Empty\n");
    }
    // Return the topmost element
    return stack->data[--stack->size];
}

void *stack_find(Stack *stack, void *element)
{
    for (size_t i = 0; stack->size; i++)
    {
        if (stack->data[i] == element)
        {
            return stack->data[i];
        }
    }
}

void stack_remove(Stack *stack, void *element)
{
    for (size_t i = 0; stack->size; i++)
    {
        if (stack->data[i] == element)
        {
            stack->data[i] = NULL;
            stack_update(stack);
            return;
        }
    }
}

void stack_push(Stack *s, void *element)
{
    // If the stack is full, we cannot push an element into it as there is no space for it.
    if (stack_full(s))
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

void stack_pop(Stack *s)
{
    // If stack size is zero then it is empty. So we cannot pop
    if (stack_empty(s))
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

void stack_clear(Stack *stack)
{
    stack->size = 0;
}
