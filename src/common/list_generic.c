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

#include "common/list_types.h"
#include "common/list_generic.h"

#if defined(LIST_T)
#include "common/template.h"

LIST_T *TEMPLATE(list_new, LIST_T)()
{
    LIST_T *list = malloc(sizeof(*list));
    list->first = NULL;
    list->last  = NULL;
    list->count = 0;
    return list;
}

void TEMPLATE(list_delete, LIST_T)(LIST_T *list)
{
    _LIST_FOREACH(list, first, next, cur)
    {
        if (cur->prev)
        {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void TEMPLATE(list_remove, LIST_T)(LIST_T *list, NODE_T *node)
{
    // check(list->first && list->last, "List is empty.");
    // check(node, "node can't be NULL");

    if (node == list->first && node == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else if (node == list->first)
    {
        list->first = node->next;
        list->first->prev = NULL;
    }
    else if (node == list->last)
    {
        list->last = node->prev;
        list->last->next = NULL;
    }
    else
    {
        NODE_T *after = node->next;
        NODE_T *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    free(node);
}


void TEMPLATE(list_clear, LIST_T)(LIST_T *list)
{
    _LIST_FOREACH(list, first, next, cur)
    {
        free(cur->data);
        cur->data = (T)NULL;
    }
}

void TEMPLATE(list_push, LIST_T)(LIST_T *list, T value)
{
    NODE_T *node = TEMPLATE(node_new, NODE_T)(value);

    if (list->last == NULL)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->count++;
}

void TEMPLATE(list_push_front, LIST_T)(LIST_T *list, T item)
{
    // Add a element at the beginning of the queue
    NODE_T *node = TEMPLATE(node_new, NODE_T)(item);
    node->next = list->first;

    if (list->first != NULL)
    {
      list->first->prev = node;
    }
    else if (list->first == NULL)
    {
        list->last = node;
    }

    list->first = node;
    list->count++;
}

void TEMPLATE(list_push_rear, LIST_T)(LIST_T *list, T item)
{
    // add element at the end of the queue

    NODE_T *node = TEMPLATE(node_new, NODE_T)(item);
    node->next = list->last;

    if (list->last != NULL)
    {
        list->last->prev = list->last->next;
        list->last->next = node;
    }
    else if (list->last == NULL)
    {
        list->first = node;
    }

    list->last = node;
    list->count++;
}

void TEMPLATE(list_pop_front, LIST_T)(LIST_T *list)
{
    if (list->first == NULL)
    {
        ERROR("Deque underflow! Unable to remove!\n");
        return;
    }
    // remove an item from the beginning of the queue
    NODE_T *tmp_front = list->first->next;

    if (tmp_front != NULL)
    {
        tmp_front->prev = NULL;
    }
    else if (tmp_front == NULL)
    {
        list->last = NULL;
    }

    list->first = tmp_front;
    list->count--;
}

void TEMPLATE(list_pop_rear, LIST_T)(LIST_T *list)
{
    if (list->last == NULL)
    {
        ERROR("Deque underflow! Unable to remove!\n");
        return;
    }
    // remove an item from the beginning of the queue
    NODE_T *tmp_rear = list->last->prev;
    if (tmp_rear != NULL)
    {
        tmp_rear->next = NULL;
    }
    else if (tmp_rear == NULL)
    {
        list->first = NULL;
    }

    list->last = tmp_rear;
    list->count--;
}


#else

#define LIST_T ListChar
#define NODE_T ListNodeChar
#define T char
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.c"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T


#endif
