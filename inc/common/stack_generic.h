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

#include "stack_types.h"

#ifndef STACK_NEW
#define STACK_NEW(T, capacity) \
TEMPLATE(stack_new, T)(capacity)
#endif

#ifndef STACK_RESIZE
#define STACK_RESIZE(T, S, capacity) \
TEMPLATE(stack_resize, T)(S, capacity)
#endif

#ifndef STACK_DELETE
#define STACK_DELETE(T, S) \
TEMPLATE(stack_delete, T)(S)
#endif

#ifndef STACK_EMPTY
#define STACK_EMPTY(T, S) \
TEMPLATE(stack_empty, T)(S)
#endif

#ifndef STACK_FULL
#define STACK_FULL(T, S) \
TEMPLATE(stack_full, T)(S)
#endif

#ifndef STACK_UPDATE
#define STACK_UPDATE(T, S) \
TEMPLATE(stack_update, T)(S)
#endif

#ifndef STACK_TOP
#define STACK_TOP(T, S) \
TEMPLATE(stack_top, T)(S)
#endif

#ifndef STACK_PUSH
#define STACK_PUSH(T, S, element) \
TEMPLATE(stack_push, T)(S, element)
#endif

#ifndef STACK_POP
#define STACK_POP(T, S) \
TEMPLATE(stack_pop, T)(S)
#endif

#ifndef STACK_CLEAR
#define STACK_CLEAR(T, S) \
TEMPLATE(stack_clear, T)(S)
#endif

#if defined(STACK_T)
#include "template.h"


STACK_T *TEMPLATE(stack_new, STACK_T)(size_t capacity);
void *TEMPLATE(stack_resize, STACK_T)(STACK_T *stack, size_t capacity);
void TEMPLATE(stack_delete, STACK_T)(STACK_T *stack);
bool TEMPLATE(stack_empty, STACK_T)(STACK_T *stack);
bool TEMPLATE(stack_full, STACK_T)(STACK_T *stack);
StackErrorCode TEMPLATE(stack_update, STACK_T)(STACK_T *stack);
T TEMPLATE(stack_top, STACK_T)(STACK_T *stack);
T TEMPLATE(stack_find, STACK_T)(STACK_T *stack, T element);
StackErrorCode TEMPLATE(stack_remove, STACK_T)(STACK_T *stack, T element);
void TEMPLATE(stack_push, STACK_T)(STACK_T *stack, T element);
void TEMPLATE(stack_pop, STACK_T)(STACK_T *stack);
void TEMPLATE(stack_clear, STACK_T)(STACK_T *stack);


#elif !defined(STACK_H_)
#define STACK_H_

#define STACK_T Stack_s8
#define T int8_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_u8
#define T uint8_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_s16
#define T int16_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_u16
#define T uint16_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_s32
#define T int32_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_u32
#define T uint32_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_s64
#define T int64_t
#include "stack_generic.h"
#undef T
#undef STACK_T

#define STACK_T Stack_u64
#define T uint64_t
#include "stack_generic.h"
#undef T
#undef STACK_T


#endif