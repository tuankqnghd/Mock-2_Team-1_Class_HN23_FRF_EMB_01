#include <stdint.h>
#include "queue.h"

static Queue q;

void initQueue() {
    q.front = 0;
    q.rear = 0;
}

uint8_t isQueueEmpty() {
  	return (q.front == q.rear);
}

uint8_t isQueueFull() {
  return ((q.rear + 1) % QUEUE_SIZE == q.front);
}

void enqueue(uint8_t value) {
    if (isQueueFull()) {
        // Queue is full
        return;
    }

    q.data[q.rear] = value;
    q.rear = (q.rear + 1) % QUEUE_SIZE;
}

uint8_t dequeue() {
    if (isQueueEmpty()) {
        // Queue is empty
        return 0; // Or any other appropriate value
    }
    
    uint8_t value = q.data[q.front];
    q.front = (q.front + 1) % QUEUE_SIZE;
    return value;
}

uint8_t front() {
    if (isQueueEmpty()) {
        // Queue is empty
        return 0; // Or any other appropriate value
    }
    
    return q.data[q.front];
}

uint8_t queueSize() {
    if (q.rear >= q.front) {
        return q.rear - q.front;
    } else {
        return QUEUE_SIZE - (q.front - q.rear);
    }
}

//void display() {
//    if (isQueueEmpty()) {
//        // Queue is empty
//        printf("Queue is empty.\n");
//        return;
//    }
//
//    uint8_t i = q.front;
//    while (i != q.rear) {
//        printf("%u ", q.data[i]);
//        i = (i + 1) % QUEUE_SIZE;
//    }
//    printf("\n");
//}
