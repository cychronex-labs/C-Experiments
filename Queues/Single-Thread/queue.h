#ifndef QUEUE_H
#define QUEUE_H

// 1. Blueprint for the Node
typedef struct Node {
    struct Node * next;
    int data;
} Node;

// 2. Blueprint for the Queue
typedef struct Queue {
    Node * head;
    Node * tail;
} Queue;

// 3. The Public API (Function Signatures)
void init_queue(Queue* q);
void enqueue(Queue* q, int value);
void dequeue(Queue* q, int * result);

#endif
