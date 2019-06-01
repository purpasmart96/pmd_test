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

#include "util.h"
#include "common/list_types.h"


#ifndef LIST_NEW
#define LIST_NEW(LIST_T) \
TEMPLATE(list_new, LIST_T)()
#endif

#ifndef LIST_DELETE
#define LIST_DELETE(LIST_T, S) \
TEMPLATE(list_delete, LIST_T)(S)
#endif

#ifndef LIST_PUSH
#define LIST_PUSH(LIST_T, S, element) \
TEMPLATE(list_push, LIST_T)(S, element)
#endif

#ifndef LIST_PUSH_FRONT
#define LIST_PUSH_FRONT(LIST_T, S, element) \
TEMPLATE(list_push_front, LIST_T)(S, element)
#endif

#ifndef LIST_PUSH_REAR
#define LIST_PUSH_REAR(LIST_T, S, element) \
TEMPLATE(list_push_rear, LIST_T)(S, element)
#endif

#ifndef LIST_POP_FRONT
#define LIST_POP_FRONT(LIST_T, S) \
TEMPLATE(list_pop_front, LIST_T)(S)
#endif

#ifndef LIST_POP_REAR
#define LIST_POP_REAR(LIST_T, S) \
TEMPLATE(list_pop_rear, LIST_T)(S)
#endif

#ifndef LIST_TO_ARRAY
#define LIST_TO_ARRAY(LIST_T, S) \
TEMPLATE(list_to_array, LIST_T)(S)
#endif

#ifndef LIST_AT
#define LIST_AT(LIST_T, S, INDEX) \
TEMPLATE(list_at, LIST_T)(S, INDEX)
#endif

#if defined(LIST_T)
#include "common/template.h"

NODE_T *TEMPLATE(node_new, NODE_T)(T data);
LIST_T *TEMPLATE(list_new, LIST_T)();
void TEMPLATE(list_delete, LIST_T)(LIST_T *list);
void TEMPLATE(list_remove, LIST_T)(LIST_T *list, NODE_T *node);
void TEMPLATE(list_remove_node, LIST_T)(LIST_T *list, T value);
void TEMPLATE(list_clear, LIST_T)(LIST_T *list);
void TEMPLATE(list_push, LIST_T)(LIST_T *list, T value);
void TEMPLATE(list_push_front, LIST_T)(LIST_T *list, T item);
void TEMPLATE(list_push_rear, LIST_T)(LIST_T *list, T item);
void TEMPLATE(list_pop_front, LIST_T)(LIST_T *list);
void TEMPLATE(list_pop_rear, LIST_T)(LIST_T *list);
void TEMPLATE(list_insert, LIST_T)(LIST_T *list, T item, int index);
T *TEMPLATE(list_to_array, LIST_T)(LIST_T *list);
T TEMPLATE(list_at, LIST_T)(LIST_T *list, int index);

#elif !defined(LIST_H_)
#define LIST_H_

#define LIST_T ListChar
#define NODE_T ListNodeChar
#define T char
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.h"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T

#define LIST_T ListInt
#define NODE_T ListNodeInt
#define T int
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.h"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T

#define LIST_T ListCharPtr
#define NODE_T ListNodeCharPtr
#define T u8 *
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.h"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T

#define LIST_T ListTexture
#define NODE_T ListNodeTexture
#define T struct Texture_s *
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.h"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T


#endif
