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

NODE_T *TEMPLATE(node_new, NODE_T)(T data)
{
    NODE_T *node = malloc(sizeof(*node));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;
    return node;
}

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
        memset(&cur->data, NULL, sizeof(T));
    }
}

void TEMPLATE(list_insert, LIST_T)(LIST_T *list, T item, int index)
{
    NODE_T *new_item = TEMPLATE(node_new, NODE_T)(item);
    int current_index = 0;
    NODE_T *current_item = list->first;
    NODE_T *prev_item = NULL;

    while (current_index < index)
    {
        prev_item = current_item;
        current_item = current_item->next;
        current_index++;
    }

    if (index == 0)
    {
        new_item->prev = list->first->prev;
        new_item->next = list->first;
        list->first->prev = new_item;
        list->first = new_item;
    }
    else if (index == list->count)
    {
        new_item->prev = list->last;
        list->last->next = new_item;
        new_item = list->last;
    }
    else
    {
        new_item->next = prev_item->next;
        prev_item->next = new_item;
        new_item->prev = current_item->prev;
        current_item->prev = new_item;
    }

    list->count++;
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
    //if (list->first == NULL)
    //{
    //    ERROR("Deque underflow! Unable to remove!\n");
    //    return;
    //}
    //// remove an item from the beginning of the queue
    //NODE_T *tmp_front = list->first->next;

    //if (tmp_front != NULL)
    //{
    //    tmp_front->prev = NULL;
    //}
    //else if (tmp_front == NULL)
    //{
    //    list->last = NULL;
    //}

    //list->first = tmp_front;
    //list->count--;

    NODE_T *node = list->first;
    LIST_REMOVE(LIST_T, list, node);

}

void TEMPLATE(list_pop_rear, LIST_T)(LIST_T *list)
{
    if (list->last == NULL)
    {
        ERROR("Deque underflow! Unable to remove!\n");
        return;
    }
    // remove an item from the end of the queue
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

/* Takes head pointer of the linked list and index
as arguments and return data at index*/
T TEMPLATE(list_at, LIST_T)(LIST_T *list, int index)
{
    NODE_T *current = list->first;
    int count = 0;

    while (current != NULL)
    {
        if (count == index)
        {
            return current->data;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

T *TEMPLATE(list_to_array, LIST_T)(LIST_T *list)
{
    T *ret_array = malloc(sizeof(T) * list->count);

    int i = 0;

    _LIST_FOREACH(list, first, next, cur)
    {
        ret_array[i++] = cur->data;
    }

    return ret_array;
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

#define LIST_T ListInt
#define NODE_T ListNodeInt
#define T int
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.c"
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
#include "list_generic.c"
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
#include "list_generic.c"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T

#define LIST_T ListBuffer
#define NODE_T ListNodeBuffer
#define T struct VertexBuffer_s *
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.c"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T

#define LIST_T ListRenderer2DInfo
#define NODE_T ListNodeRenderer2DInfo
#define T struct Renderer2DInfo_s *
#define _LIST_FOREACH(L, S, M, V) NODE_T *_node = NULL;\
    NODE_T *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)
#include "list_generic.c"
#undef _LIST_FOREACH
#undef T
#undef NODE_T
#undef LIST_T


#endif
