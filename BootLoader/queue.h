#ifndef QUEUE_H
#define QUEUE_H

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"

/********************************************************************
 * API
********************************************************************/

#define QUEUE_SIZE 256

typedef struct {
  uint8_t* data[QUEUE_SIZE];
  uint32_t front;
  uint32_t rear;
} Queue;

void initQueue(Queue* q);
uint8_t isQueueEmpty(Queue* q);
uint8_t isQueueFull(Queue* q);
void enqueue(Queue* q, uint8_t* value);
uint8_t* dequeue(Queue* q);
int size(Queue* q);

#endif

