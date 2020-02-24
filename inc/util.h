// Copyright(c) 2015 <Purpasmart>
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


#ifndef _UTIL_H_
#define _UTIL_H_

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#undef ERROR
#else
#include <unistd.h>
#endif

#include "common/strlcpy.h"
#include <stdlib.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "common/types.h"

typedef struct
{
    u64 raw : 48;
} u48;

/// Creates a bitmask from a bit number.
#define BIT(n) (1u << (n))

#ifdef CONST
#undef CONST
#endif

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifdef _WIN32
static WORD _wincolors[] = {
    0,                                                          // black
    FOREGROUND_RED | FOREGROUND_INTENSITY,                    // red
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,                    // green
    FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,   // yellow
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,                    // blue
    FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,   // magenta
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, // cyan
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, // white
};
#endif

static int set_color(int color)
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
        &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        _wincolors[color]);

    return csbiInfo.wAttributes;
#else
    fprintf(stdout, "\033[0;%dm", color + 30);
    return 0;
#endif
}

static int color_red() { return set_color(1); }
static int color_green() { return set_color(2); }
static int color_yellow() { return set_color(3); }
static int color_teal()  { return set_color(6); }

static void color_restore(int old)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)old);
#else
    fprintf(stdout, "\033[0m");
#endif
}

#ifndef DISABLE_DEBUG
#define DEBUG(...) do {                                 \
        int old = color_green();                        \
        fprintf(stdout, "%s (line %d): ", __func__, __LINE__);              \
        color_restore(old);                             \
        fprintf(stdout, __VA_ARGS__);                   \
} while (0)
#else
#define DEBUG(...) ((void)0)
#endif

#define ERROR(...) do {                                 \
        int old = color_red();                          \
        fprintf(stdout, "%s: ", __func__);              \
        color_restore(old);                             \
        fprintf(stdout, __VA_ARGS__);       			\
    } while(0)


#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define CLAMP( X, MIN, MAX )  ( (X)<(MIN) ? (MIN) : ((X)>(MAX) ? (MAX) : (X)) )

// Minimum and maximum of three values
#define MIN3( X, Y, Z ) ((X) < (Y) ? MIN(X, Z) : MIN(Y, Z))
#define MAX3( X, Y, Z ) ((X) > (Y) ? MAX(X, Z) : MAX(Y, Z))

#define ARRAY_SIZE(s) (sizeof(s)/sizeof((s)[0]))

#define foreach(item, array) \
    for(size_t keep = 1, \
            count = 0,\
            _size = sizeof (array) / sizeof *(array); \
        keep && count != _size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

/*
#define FOR_EACH(item, array, length) \
    for(int keep = 1, count = 0, _size = length; \
			keep && count != _size; \
			keep = !keep, count++) \
      for (item = (array) + count; keep; keep = !keep)
*/

#define FOR_EACH(item, array, size) \
    for(size_t i = 0, keep = 1;\
        keep && i < size;\
        keep = !keep, i++)\
    for (item = array[i]; keep; keep = !keep)

typedef struct Texture_s
{
    char *name;
    u8 *image;
    int sampler;
    int id;
    int internal_format; // Format of texture object
    int image_format; // Format of loaded image
    int wrap_s; // Wrapping mode on S axis
    int wrap_t; // Wrapping mode on T axis
    int filter_min; // Filtering mode if texture pixels < screen pixels
    int filter_max; // Filtering mode if texture pixels > screen pixels
    u32 width;
    u32 height;

} Texture_t;


#endif
