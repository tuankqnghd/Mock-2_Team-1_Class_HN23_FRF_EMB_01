/*
* @file BootLoader.c
* @brief BootLoader.c support software loading and selecting firmware 
to run
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
  // Config Button 1 & 2
  BTN_Config();
      
  // Config Systick
  Systick_Init();
  
  // Config UART for load program
  UART_User_Config();

  // Init Queue
  initQueue();
  
  // Delay 5s
  Systick_Delay_5s();

  // Disable INT for portC_portD 
  NVIC_DisableIRQ(PORTC_PORTD_IRQn);
   
  // Select Firmware1 or 2 Mode or Bootloader (Write to Flash)
  Mode_Selection();
   
  // If Bootloader mode init for load program to flash
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