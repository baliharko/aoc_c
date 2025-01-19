#pragma once

#include <stddef.h>
#define QUEUE_SIZE 1024
#define MAX_ELEMENT_SIZE 256

typedef struct {
    unsigned char data[QUEUE_SIZE * MAX_ELEMENT_SIZE];
    size_t elementSize;
    int front;
    int back;
    int count;
} Queue;

void initQueue(Queue *q, size_t elementSize);
void enqueue(Queue *q, const void *item);
void dequeue(Queue *q, void *item);
