#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    struct Node * next;
    int data;
} Node;

typedef struct Queue {
    Node * head;
    Node * tail;
} Queue;

void init_queue(Queue* q);
void enqueue(Queue* q, int value);
void dequeue(Queue* q, int * result);

#endif
