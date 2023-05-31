#include "queue.h"


void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

uint8_t isQueueEmpty(Queue* q) {
  	return (q->front == q->rear);
}

uint8_t isQueueFull(Queue* q) {
  return ((q->rear + 1) % QUEUE_SIZE == q->front);
}

void enqueue(Queue* q, uint8_t value) {
    if (isQueueFull(q)) {
        // Queue is full
        return;
    }

    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
}

uint8_t dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        // Queue is empty
        return 0; // Or any other appropriate value
    }
    
    uint8_t value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return value;
}

uint8_t front(Queue* q) {
    if (isQueueEmpty(q)) {
        // Queue is empty
        return 0; // Or any other appropriate value
    }
    
    return q->data[q->front];
}

uint8_t queueSize(Queue* q) {
    if (q->rear >= q->front) {
        return q->rear - q->front;
    } else {
        return QUEUE_SIZE - (q->front - q->rear);
    }
}
