
/*
* Copyright (C) 2016 - purpasmart
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "util.h"

#ifndef _LIST_TYPES_H_
#define _LIST_TYPES_H_

typedef struct ListNodeChar
{
    struct ListNodeChar *next;
    struct ListNodeChar *prev;
    char data;
} ListNodeChar;

typedef struct
{
    u32 count;
    ListNodeChar *first;
    ListNodeChar *last;
} ListChar;

typedef struct ListNodeInt
{
    struct ListNodeInt *next;
    struct ListNodeInt *prev;
    int data;
} ListNodeInt;

typedef struct ListInt
{
    u32 count;
    ListNodeInt *first;
    ListNodeInt *last;
} ListInt;

typedef struct ListNodeCharPtr
{
    struct ListNodeCharPtr *next;
    struct ListNodeCharPtr *prev;
    u8 *data;
} ListNodeCharPtr;

typedef struct ListCharPtr
{
    u32 count;
    ListNodeCharPtr *first;
    ListNodeCharPtr *last;
} ListCharPtr;

typedef struct ListNodeTexture
{
    struct ListNodeTexture *next;
    struct ListNodeTexture *prev;
    struct Texture_s *data;
} ListNodeTexture;

typedef struct ListTexture
{
    u32 count;
    ListNodeTexture *first;
    ListNodeTexture *last;
} ListTexture;

typedef struct ListNodeBuffer
{
    struct ListNodeBuffer *next;
    struct ListNodeBuffer *prev;
    struct VertexBuffer_s *data;
} ListNodeBuffer;

typedef struct ListBuffer
{
    u32 count;
    ListNodeBuffer *first;
    ListNodeBuffer *last;
} ListBuffer;

typedef struct ListNodeRenderer2DInfo
{
    struct ListNodeRenderer2DInfo *next;
    struct ListNodeRenderer2DInfo *prev;
    struct Renderer2DInfo_s *data;
} ListNodeRenderer2DInfo;

typedef struct ListRenderer2DInfo
{
    u32 count;
    ListNodeRenderer2DInfo *first;
    ListNodeRenderer2DInfo *last;
} ListRenderer2DInfo;

#endif
