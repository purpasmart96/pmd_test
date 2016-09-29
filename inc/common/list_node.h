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

#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#include "util.h"

typedef struct ListNode
{
    struct ListNode *next;
    struct ListNode *prev;
    void   *data;
} ListNode;

typedef struct
{
    u32 count;
    ListNode *first;
	   ListNode *last;
} List;

#define TYPED_STRUCT(NAME, T) struct NAME##_##T
                                                                     

#define DEFINE_LL_NODE(T) \
typedef struct list_node_##TYPE \
{ \
    CONCRETE_TYPE data; \
    struct list_node_##T *next; \
    struct list_node_##T *prev; \
}ListNode_##TYPE; \
 \
typedef struct list_##T \
{ \
    u32 count; \
    ListNode_##T  *first;\
	   ListNode_##T  *last; \
} List_##T;

#define DECLARE_LL_NODE(TYPE, NAME) \
  struct list_node_##TYPE NAME;

#define DECLARE_LL_LIST(TYPE, NAME) \
  struct list_##TYPE NAME;

#define GENERIC_LIST(x) _Generic((x), \
    long double complex: cacosl, \
    double complex: cacos, \
    float complex: cacosf, \
    long double: acosl, \
    float: acosf, \
    default: acos \
    )(X) \
typedef struct list_##TYPE \
{ \
    u32 count; \
    ListNode_##TYPE  *first;\
	   ListNode_##TYPE  *last; \
} List_##TYPE;


typedef struct
{
    u32 count;
    ListNode *head;
    ListNode *ptr;
} PriorityQueue;


List *list_New();
void list_Destroy(List *list);
void list_Clear(List *list);
void list_Clear_mutexs(List *list);
void list_Clear_threads(List *list);
void list_Clear_destroy(List *list);
void  list_Cush(List *list, void *value);
void *list_Pop(List *list);
void  list_Push_front(List *list, void *value);
void *list_Pop_front(List *list);
void *list_Remove(List *list, ListNode *node);

void list_remove_node_from_key(List *list, void *key);
ListNode *list_find_node(List *list, void *key);
void *list_find_key(List *list, void *key);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#define PROCESS_LIST_FOREACH(L, S, M, V) ProcessNode *_node = NULL;\
    ProcessNode *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#define THREAD_LIST_FOREACH(L, S, M, V) struct thread *_node = NULL;\
    struct thread *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)


void push_front(List *list, void *item);
     
void push_rear(List *list, void *item);
     
void pop_front(List *list);
     
void pop_rear(List *list);
void list_remove_node(List *list, ListNode *node);




#endif
