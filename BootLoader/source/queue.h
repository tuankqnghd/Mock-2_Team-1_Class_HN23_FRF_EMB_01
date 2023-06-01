#ifndef QUEUE_H
#define QUEUE_H

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "types.h"

/********************************************************************
 * Definition
********************************************************************/

#define QUEUE_SIZE (256u)

typedef struct {
    uint8 data[QUEUE_SIZE];
    uint8 front;
    uint8 rear;
} Queue;

/*********************************************************************
* Variable
*********************************************************************/

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/


/* Function Prototypes */

/*
* @brief init queue
*
*@return void
*/
void initQueue();



/*
* @brief check queue is empty or not
*
*@return 0 : Queue is not empty - 1: Queue empty
*/
uint8 isQueueEmpty();



/*
* @brief check queue is full or not
*
*@return 0 : Queue is not full - 1: Queue full
*/
uint8 isQueueFull();



/*
* @brief enter a data to last of queue
*
*@param value is data need to enter queue
*
*@return void
*/
void enqueue(uint8 value);



/*
* @brief take the first data of queue
*
*@param value is data need to enter queue
*
*@return void
*/
uint8 dequeue();



/*
* @brief check position of front data in queue
*
*@return index of front data
*/
uint8 front();



/*
* @brief check queue's size
*
*@return queue size
*/
uint8 queueSize();



//void display();

#endif /* __QUEUE_H__ */

