#include <pthread.h>
#include <stdlib.h>
#include <threads.h>
#include "queue.h"

void init_queue(Queue *q){
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void enqueue(Queue *q, int value){
    pthread_mutex_lock(&(q->mutex));

    Node * node = malloc(sizeof(Node));
    node -> data = value;
    node -> next = NULL;
    if(q->head == NULL){
        q->head = node;
        q->tail = node;
    }else{
        q->tail->next = node;
        q->tail = node;
    };
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&(q->mutex));

}

void dequeue(Queue *q, int *result){
    pthread_mutex_lock(&(q->mutex));
    while( q->head == NULL ){
        pthread_cond_wait(&q->cond, &q->mutex);
    }
    Node * temp_ptr = q->head;
    *result = q->head->data;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp_ptr);

    pthread_mutex_unlock(&(q->mutex));
}
