// Copyright(c) <2015> <Purpasmart>
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


#include "common/queue.h"

void queue_init(Queue *q, int capacity)
{
    q->capacity = capacity;
    q->data = (u32*)malloc(sizeof(u32) * q->capacity);
    q->size = 0;
    q->front = 0;
    q->rear = -1;
}

bool queue_empty(Queue *q)
{
    if (q->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void dequeue(Queue *q)
{
    // If Queue size is zero then it is empty. So we cannot pop
    if (q->size == 0)
    {
        ERROR("Queue is Empty\n");
        return;
    }
    else
    {
        // Removing an element is equivalent to incrementing index of front by one
        q->size--;
        q->front++;

        // As we fill elements in circular fashion
        if (q->front == q->capacity)
        {
            q->front = 0;
        }
    }
    return;
}

int queue_front(Queue *q)
{
    if (q->size == 0)
    {
        ERROR("Queue is Empty\n");
    }
    // Return the element which is at the front
    return q->data[q->front];
}

void enqueue(Queue *q, int element)
{
    // If the Queue is full, we cannot push an element into it as there is no space for it.
    if (q->size == q->capacity)
    {
        ERROR("Queue is Full\n");
    }
    else
    {
        q->size++;
        q->rear = q->rear + 1;

        // As we fill the queue in circular fashion
        if (q->rear == q->capacity)
        {
            q->rear = 0;
        }
        // Insert the element in its rear side
        q->data[q->rear] = element;
    }
    return;
}
