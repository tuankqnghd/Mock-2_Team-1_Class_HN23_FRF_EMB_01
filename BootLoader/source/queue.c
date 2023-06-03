/*
* @file queue.c
* @brief queue.c lib support init queue, enqueue and dequeue, ...
*/
/********************************************************************
 * Include Library
********************************************************************/

#include "queue.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static Queue q;

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/



void initQueue() 
{
  q.front = 0;
  q.rear = 0;
}



uint8 isQueueEmpty() 
{
  return (q.front == q.rear);
}



uint8 isQueueFull() 
{
  return ((q.rear + 1) % QUEUE_SIZE == q.front);
}



void enqueue(uint32 address, uint32 data) 
{
  if (isQueueFull()) 
  {
    // Queue is full
    return;
  }
  q.flashdata[q.rear].address = address;
  q.flashdata[q.rear].data = data;
  q.rear = (q.rear + 1) % QUEUE_SIZE;
}



FlashData dequeue() {
  FlashData value;
  if (isQueueEmpty())
  {
    value.address = 0;
    value.data = 0;
    // Queue is empty
    return value; // Or any other appropriate value
  }
    
  value = q.flashdata[q.front];
  q.front = (q.front + 1) % QUEUE_SIZE;
  return value;
}



uint8 queueSize() 
{
  if (q.rear >= q.front) 
  {
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
//    uint8 i = q.front;
//    while (i != q.rear) {
//        printf("%u %u ", q.flashdata[i].address, q.flashdata[i].data);
//        i = (i + 1) % QUEUE_SIZE;
//    }
//    printf("\n");
//}
