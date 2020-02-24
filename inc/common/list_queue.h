// Copyright(c) 2020 Purpasmart
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

#ifndef _LIST_QUEUE_H_
#define _LIST_QUEUE_H_

#include "util.h"

typedef struct Node_s
{
    void *data;
    struct Node_s *next;
    struct Node_s *prev;
} Node_t;

typedef struct Queue_s
{
    struct Node_s *front;
    struct Node_s *back;
    int size;
} Queue_t;

void Node_Delete(Queue_t * queue, Node_t *node);

Queue_t *Queue_New();

void Queue_PushFront(Queue_t *queue, void * data);

void Queue_PushBack(Queue_t *queue, void * data);

void Queue_PopFront(Queue_t *queue);

void Queue_PopBack(Queue_t *queue);
void Queue_Clear(Queue_t *queue);
void Queue_ShutDown(Queue_t *queue);

#endif
