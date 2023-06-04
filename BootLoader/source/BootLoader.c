/*
* @file BootLoader.c
* @brief BootLoader.c support software loading and selecting to run
KL46
*/
/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "Middleware.h"
#include "types.h"

/********************************************************************
 * Definition
********************************************************************/

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


void main()
{
  BTN_Config();
  
  // Config PIT interupt after 5s
  PIT_Config_5s();
  
  // Config UART for load program
  UART_User_Config();
  
  // Init Queue
  initQueue();
    
  // Set new Vector Table
  Copy_Vector_Table_SetVTOR();
  
  while(1)
  {
    if (!isQueueEmpty())
    {
      FirmwaretoFlash();
    }
  }
}