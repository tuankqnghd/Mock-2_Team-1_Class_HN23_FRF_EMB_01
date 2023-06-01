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
  SystemCoreClockUpdate();
  
  // Config LED and button
  RED_LED_Config();
  
  BLUE_LED_Config();
  
  BTN1_Config();
  
  // Config PIT interupt after 5s
  PIT_Config_5s();
  
  // Config UART for load program
  UART_User_Config();
  
  // Init Queue
  initQueue();
    
  // Set new Vector Table
  Copy_Vector_Table_SetVTOR();
  
  Flash_WriteWord(0x00001000u, 0xABCDEF12u);
  
  Flash_WriteWord(0x00001004u, 0xABCDEF12u);
  
  Flash_WriteWord(0x000010A0u, 0xABCDEF12u);
  
  Flash_EraseSector(0x00001000u);
  
  while(1)
  {

  }
}