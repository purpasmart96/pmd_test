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

#include "common/list_queue.h"

static Node_t *Node_New(void *data)
{
    Node_t *node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    return node;
}

void Node_Delete(Queue_t *queue, Node_t *node)
{
    // check(list->first && list->last, "List is empty.");
    // check(node, "node can't be NULL");

    if (node == queue->front && node == queue->back)
    {
        queue->front = NULL;
        queue->back = NULL;
    }
    else if (node == queue->front)
    {
        queue->front = node->next;
        queue->front->prev = NULL;
    }
    else if (node == queue->back)
    {
        queue->back = node->prev;
        queue->back->next = NULL;
    }
    else
    {
        Node_t *after = node->next;
        Node_t *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    queue->size--;
    free(node);
}

Queue_t *Queue_New()
{
    Queue_t *queue = malloc(sizeof(*queue));
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
    return queue;
}

void Queue_PushFront(Queue_t *queue, void *data)
{
    Node_t* new_node = Node_New(data);
    // If true then new element cannot be added
    // and it is an 'Overflow' condition
    if (new_node == NULL)
    {
        printf("OverFlow\n");
    }
    else
    {
        // If deque is empty
        if (queue->front == NULL)
            queue->back = queue->front = new_node;

        // Inserts node at the front end
        else
        {
            new_node->next = queue->front;
            queue->front->prev = new_node;
            queue->front = new_node;
        }

        // Increments count of elements by 1
        queue->size++;
    }
}

void Queue_PushBack(Queue_t *queue, void *data)
{
    Node_t* new_node = Node_New(data);
    // If true then new element cannot be added
    // and it is an 'Overflow' condition
    if (new_node == NULL)
    {
        printf("OverFlow\n");
    }
    else
    {
        // If deque is empty
        if (queue->back == NULL)
            queue->front = queue->back = new_node;

        // Inserts node at the back end
        else
        {
            new_node->prev = queue->back;
            queue->back->next = new_node;
            queue->back = new_node;
        }

        // Increments count of elements by 1
        queue->size++;
    }
}

// Function to delete the element
// from the front end
void Queue_PopFront(Queue_t *queue)
{
    // If deque is empty then
    // 'Underflow' condition
    if (queue->size == 0)
        printf("UnderFlow\n");

    // Deletes the node from the front end and makes
    // the adjustment in the links
    else
    {
        Node_t* temp = queue->front;
        queue->front = queue->front->next;

        // If only one element was present
        if (queue->front == NULL)
            queue->back = NULL;
        else
            queue->front->prev = NULL;
        free(temp);

        // Decrements count of elements by 1
        queue->size--;
    }
}

// Function to delete the element
// from the rear end
void Queue_PopBack(Queue_t *queue)
{
    // If deque is empty then
    // 'Underflow' condition
    if (queue->size == 0)
        printf("UnderFlow\n");

    // Deletes the node from the rear end and makes
    // the adjustment in the links
    else
    {
        Node_t* temp = queue->back;
        queue->back = queue->back->prev;

        // If only one element was present
        if (queue->back == NULL)
            queue->front = NULL;
        else
            queue->back->next = NULL;
        free(temp);

        // Decrements count of elements by 1
        queue->size--;
    }
}

void *Queue_At(Queue_t *queue, int index)
{
    Node_t *current = queue->front;
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

void Queue_Clear(Queue_t *queue)
{
    queue->back = NULL;
    while (queue->front != NULL)
    {
        Node_t* temp = queue->front;
        queue->front = queue->front->next;
        //free(temp->data);
        free(temp);
    }
    queue->size = 0;
}

void Queue_ShutDown(Queue_t *queue)
{
    LIST_FOREACH(queue, front, next, cur)
    {
        if (cur->prev)
        {
            free(cur->prev);
        }
    }

    free(queue->back);
    free(queue);
}

