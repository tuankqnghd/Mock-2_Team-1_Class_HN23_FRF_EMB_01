#ifndef QUEUE_H
#define QUEUE_H

#include "stdint.h"

#define QUEUE_SIZE (256u)

typedef struct {
    uint8_t data[QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
} Queue;

void initQueue();
uint8_t isQueueEmpty();
uint8_t isQueueFull();
void enqueue(uint8_t value);
uint8_t dequeue();
uint8_t front();
uint8_t queueSize();
//void display();

#endif

