#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void initQueue(Queue *q, size_t elementSize) {
    assert(q != NULL);

    if (elementSize > MAX_ELEMENT_SIZE) {
        printf("Error: Element size exceeds the maximum allowed size.\n");
        return;
    }

    q->elementSize = elementSize;
    q->front = 0;
    q->back = -1;
    q->count = 0;
}

void enqueue(Queue *q, const void *item) {
    if (q->count == QUEUE_SIZE) {
        printf("Queue is full.\n");
        return;
    }

    q->back = (q->back + 1) % QUEUE_SIZE;

    size_t offset = q->back * q->elementSize;
    memcpy(&(q->data[offset]), item, q->elementSize);
    q->count++;
}

void dequeue(Queue *q, void *item) {
    if (q->count == 0) {
        printf("Queue is empty.\n");
        return;
    }

    size_t offset = q->front * q->elementSize;
    memcpy(item, &(q->data[offset]), q->elementSize);

    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;
}
