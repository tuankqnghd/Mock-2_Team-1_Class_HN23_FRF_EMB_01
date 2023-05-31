#ifndef QUEUE_H
#define QUEUE_H

#include "MKL46Z4.h"

#define QUEUE_SIZE 100

typedef struct {
    uint8_t data[QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
} Queue;

void initQueue(Queue* q);
uint8_t isQueueEmpty(Queue* q);
uint8_t isQueueFull(Queue* q);
void enqueue(Queue* q, uint8_t value);
uint8_t dequeue(Queue* q);
uint8_t front(Queue* q);
uint8_t queueSize(Queue* q);

#endif

