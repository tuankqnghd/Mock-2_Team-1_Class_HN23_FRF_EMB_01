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
#include "BootLoader.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

typedef void (*Reset_Handeler_Ptr)(void);
Reset_Handeler_Ptr func_ptr = 0;


uint32 FIRMWARE1_START_ADD   =  0x1000;
uint32 FIRAMWARE2_START_ADD  =  0x2800;


/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

void Dis_Intterupt_Timer(void)
{
   __disable_irq();
   SysTick->CTRL = 0;
   SysTick->LOAD = 0;
}

void Dis_Fault_Hander(void)
{
  NVIC->ICPR[0] = 0xFFFFFFFF;
}

  void Jump_To_App(uint32 Add)      
  {
    // Get addres to jump to application 2
    SCB->VTOR = Add; 
    
     // Turn off  all interrupts and Systick Timers
     Dis_Intterupt_Timer();
      
     // Disable Fault Hander
     Dis_Fault_Hander();  // khong chac
    
     
     
     
     // Set main stack pointer
      __DMB();
      __set_MSP(*(volatile uint32*)Add);
      __DSB();
     // set program trong Handler
     uint32_t Jumpaddress = *( (volatile uint32_t *) (Add + 4) );
     /*void (*Reset_Handler)(void) = ( void(*)(void) )Jumpaddress; */
     
     /* Dùng con tro ham  = NULL
        - Lay dia chi moi cua Reset_Handler cho con tro ham troc vao 
        - Goi Reset Handler thong qua con tro ham 
    */
     func_ptr = ( void(*)(void) )Jumpaddress;
     func_ptr();
  }

void main()
{
//  BTN_Config();
//  
//  // Config PIT interupt after 5s
//  PIT_Config_5s();
//  
//  // Config UART for load program
//  UART_User_Config();
//  
//  // Init Queue
//  initQueue();
//    
//  // Set new Vector Table
//  Copy_Vector_Table_SetVTOR();
//  

    if (READ_BTN1() == 0)
    {
      Jump_To_App(FIRAMWARE2_START_ADD);
    }
  
  while(1)
  {
//    if (!isQueueEmpty())
//    {
//      FirmwaretoFlash();
//    }
  }
}