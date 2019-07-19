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

#include <string.h>

#include "common/stack_error.h"
#include "common/stack_generic.h"

#if defined(STACK_T)
#include "common/template.h"

STACK_T *TEMPLATE(stack_new, STACK_T)(size_t capacity)
{
    STACK_T *stack = (STACK_T*) malloc(sizeof(*stack));
    stack->capacity = capacity;
    stack->data = (T*) malloc(stack->capacity * sizeof(T));
    stack->size = 0;

    if (!stack || !stack->data)
    {
        return NULL;
    }
    return stack;
}

void *TEMPLATE(stack_resize, STACK_T)(STACK_T *stack, size_t capacity)
{
    stack->capacity = capacity;
    T *temp = (T*) realloc(stack->data, sizeof(T) * stack->capacity);

    if (!temp)
    {
        return NULL;
    }
    stack->data = temp;
}

void TEMPLATE(stack_delete, STACK_T)(STACK_T *stack)
{
    free(stack->data);
    free(stack);
}

bool TEMPLATE(stack_empty, STACK_T)(STACK_T *stack)
{
    return !stack->size;
}

bool TEMPLATE(stack_full, STACK_T)(STACK_T *stack)
{
    return stack->size == stack->capacity;
}

StackErrorCode TEMPLATE(stack_update, STACK_T)(STACK_T *stack)
{
    STACK_T *stack_temp = STACK_NEW(STACK_T, stack->capacity);

    if (!stack_temp)
    {
        goto alloc_failed;
    }
    else if (STACK_EMPTY(STACK_T, stack))
    {
        goto stack_empty;
    }

    for (size_t i = 0; i < stack->size; i++)
    {
        if (stack->data[i] != 0) // Find a non-empty slot
        {
            STACK_PUSH(STACK_T, stack_temp, stack->data[i]);
        }
    }

    memcpy(stack, stack_temp, sizeof(stack));
    STACK_DELETE(STACK_T, stack_temp);
    return STACK_SUCCESS;

// Should never happen
alloc_failed:
    STACK_DELETE(STACK_T, stack_temp);
    return STACK_ALLOC_FAILED;

stack_empty:
    STACK_DELETE(STACK_T, stack_temp);
    return STACK_EMPTY;
}

T TEMPLATE(stack_top, STACK_T)(STACK_T *stack)
{
    // Return the topmost element
    return stack->data[--stack->size];
}

T TEMPLATE(stack_find, STACK_T)(STACK_T *stack, T element)
{
    for (size_t i = 0; stack->size; i++)
    {
        if (stack->data[i] == element)
        {
            return stack->data[i];
        }
    }
}

// Removes a element from the stack and updates the stack to stay linear
StackErrorCode TEMPLATE(stack_remove, STACK_T)(STACK_T *stack, T element)
{
    if (STACK_EMPTY(STACK_T, stack))
    {
        return STACK_EMPTY;
    }

    for (size_t i = 0; stack->size; i++)
    {
        if (stack->data[i] == element)
        {
            stack->data[i] = 0;
            StackErrorCode result = STACK_UPDATE(STACK_T, stack);

            if (result != STACK_SUCCESS)
            {
                return result;
            }
        }
    }
    return STACK_SUCCESS;
}

void TEMPLATE(stack_push, STACK_T)(STACK_T *stack, T element)
{
    // Push an element on the top of it and increase its size by one
    stack->data[stack->size++] = element;
}

// If stack size is zero then it is empty. So we cannot pop,
// so it is advised to use STACK_EMPTY on the stack before popping
void TEMPLATE(stack_pop, STACK_T)(STACK_T *stack)
{
    stack->size--;
}

void TEMPLATE(stack_clear, STACK_T)(STACK_T *stack)
{
    stack->size = 0;
}


#else

#define STACK_H_

#define STACK_T Stack_s8
#define T int8_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_u8
#define T uint8_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_s16
#define T int16_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_u16
#define T uint16_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_s32
#define T int32_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_u32
#define T uint32_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_s64
#define T int64_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#define STACK_T Stack_u64
#define T uint64_t
#include "stack_generic.c"
#undef T
#undef STACK_T

#endif
