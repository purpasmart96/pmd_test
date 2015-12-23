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


#include "common/d_list.h"


Node *new_node()
{
    Node *node = NULL;
    node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void delete_node(Node *node)
{
    free(node);
}

void node_init(Node *n)
{
	n = (Node*)malloc(sizeof(Node));
	n->next = NULL;
	n->prev = NULL;
}

bool list_empty(Node *n)
{
    if (n->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void list_insert(Node *n, u32 data)
{
    // Iterate through the list till we encounter the last node.
    while (n->next != NULL)
    {
        n = n->next;
    }
    // Allocate memory for the new node and put data in it.
    n->next = (Node *)malloc(sizeof(Node));
    (n->next)->prev = n;
    n = n->next;
    n->data = data;
    n->next = NULL;
    n->size++;
}

int list_find(Node *n, u32 data)
{
    n =  n->next; // First node is dummy node.
    // Iterate through the entire linked list and search for the key. */
    while (n != NULL)
    {
        if (n->data == data) // Data is found.
        {
            return true;
        }
        else
        {
            n = n->next; // Search in the next node.
        }
    }
        // Data is not found
    return false;
}

void list_delete(Node *n, u32 data)
{
    // Go to the node for which the node next to it has to be deleted
    while (n->next != NULL && (n->next)->data != data)
    {
        n = n->next;
    }
    if (n->next == NULL)
    {
        ERROR("Element %d is not present in the list\n", data);
        return;
    }
    // Now pointer points to a node and the node next to it has to be removed */
    Node *temp;
    temp = n->next;
    // temp points to the node which has to be removed
    n->next = temp->next;
    temp->prev =  n;
    // We removed the node which is next to the pointer (which is also temp)
    free(temp);
    n->size--;
    return;
}
