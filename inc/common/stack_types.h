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

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef _STACK_TYPES_H_
#define _STACK_TYPES_H_

// Example Stack Types

typedef struct Stack_char
{
    char    *data;
    size_t   size;
    size_t   capacity;
} Stack_char;

typedef struct Stack_s8
{
    int8_t   *data;
    size_t   size;
    size_t   capacity;
} Stack_s8;

typedef struct Stack_u8
{
    uint8_t  *data;
    size_t   size;
    size_t   capacity;
} Stack_u8;

typedef struct Stack_s16
{
    int16_t  *data;
    size_t   size;
    size_t   capacity;
} Stack_s16;

typedef struct Stack_u16
{
    uint16_t *data;
    size_t   size;
    size_t   capacity;
} Stack_u16;

typedef struct Stack_s32
{
    int32_t *data;
    size_t   size;
    size_t   capacity;
} Stack_s32;

typedef struct Stack_u32
{
    uint32_t *data;
    size_t   size;
    size_t   capacity;
} Stack_u32;

typedef struct Stack_s64
{
    int64_t *data;
    size_t   size;
    size_t   capacity;
} Stack_s64;

typedef struct Stack_u64
{
    uint64_t *data;
    size_t   size;
    size_t   capacity;
} Stack_u64;

// Your Custom Stack types go here



#endif
