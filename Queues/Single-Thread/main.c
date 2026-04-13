#include <stdio.h>
#include "queue.h"

int main(void) {
    Queue q;
    int result;

    init_queue(&q);

    for (int i = 0; i <= 50; i++) {
        enqueue(&q, i);
        printf("Queued: %d\n", i);
    }

    printf("Processing 51 items...\n");

    for (int i = 0; i <= 50; i++) {
        dequeue(&q, &result);
        printf("Dequeued: %d\n", result);
    }

    return 0;
}
