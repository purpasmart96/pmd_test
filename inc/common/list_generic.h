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
#include "common/list_types.h"
#include "common/node_generic.h"


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


#if defined(LIST_T)
#include "common/template.h"

LIST_T *TEMPLATE(list_new, LIST_T)();
void TEMPLATE(list_delete, LIST_T)(LIST_T *list);
void TEMPLATE(list_remove, LIST_T)(LIST_T *list, NODE_T *node);
void TEMPLATE(list_clear, LIST_T)(LIST_T *list);
void TEMPLATE(list_push, LIST_T)(LIST_T *list, T value);
void TEMPLATE(list_push_front, LIST_T)(LIST_T *list, T item);
void TEMPLATE(list_push_rear, LIST_T)(LIST_T *list, T item);
void TEMPLATE(list_pop_front, LIST_T)(LIST_T *list);
void TEMPLATE(list_pop_rear, LIST_T)(LIST_T *list);

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


#endif
