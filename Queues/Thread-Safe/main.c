#include <stdio.h>
#include "queue.h"
#include <pthread.h>

void * thread_enqueue(void * arg){
    Queue * q = arg;
    for (int i = 0; i <= 5; i++) {
        enqueue(q, i);
        printf("Queued: %d\n", i);
    };
    return NULL;
}
void * thread_dequeue(void * arg){
    Queue * q = arg;
    int result;
    for (int i = 0; i <= 5; i++) {
        dequeue(q, &result);
        printf("Dequeued: %d\n", result);
    };
    return NULL;
}

int main(void){
    Queue q;
    pthread_t thread[10];
    init_queue(&q);
    for (int i=0; i<5;i++){
        pthread_create(&thread[i], NULL, thread_enqueue, &q);
        pthread_create(&thread[5+i], NULL, thread_dequeue, &q);
    }
    for(int i=0;i<10;i++){
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&q.mutex);
    return 0;
}
