#include <stdlib.h>
#include "queue.h"

void init_queue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(Queue* q, int value) {
    Node * new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (q->head == NULL) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

void dequeue(Queue* q, int * result) {
    if (q->head != NULL) {
        *result = q->head->data;
        Node* temp = q->head;
        q->head = q->head->next;

        if (q->head == NULL) {
            q->tail = NULL;
        }

        free(temp);
    }
}
