#include "MKL46Z4.h"
# include "Middleware.h"

typedef unsigned int uint32;
typedef unsigned char uint8;

typedef void (*Reset_Handeler_Ptr)(void);
Reset_Handeler_Ptr func_ptr = 0;


uint32 FIRMWARE1_START_ADD   =  0x1000;
uint32 FIRAMWARE2_START_ADD  =  0x2800;

//volatile uint8 ModeSelection = 0;

//typedef enum
//{
//  DEFUALT               = 0u,
//  BOOTLOADER_MODE       = 1u,
//  FIRNWARE_MODE         = 2u,
//}Run_Mode_type;

void LedGreen_INTConfig(void)
{
        // Led red == PTD5 or PORT D- PIN 5
  //Enable Clock
  SIM->SCGC5 |=  SIM_SCGC5_PORTD(1);
  // Set GPIO
  PORTD->PCR[5] &= ~PORT_PCR_MUX_MASK;
  PORTD->PCR[5] |= PORT_PCR_MUX(1);
   
  //Set Output
  FGPIOD->PDDR |= (1<<5);
  //Set den led ban dau tat
  FGPIOD->PDOR |= (1<<5);
}

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





void Firmware_Selection(void)
{
  // Kiem tra nut bam 1 - bam thi nhay vao firware 1
  if ( 0 ==  (GPIO_ReadPin(FGPIOC,3)) )
  {
     Systick_Delay(0.2);
     if ( 0 ==  (GPIO_ReadPin(FGPIOC,3)) )
     {
        Jump_To_App(FIRMWARE1_START_ADD);
        while( 0 ==  (GPIO_ReadPin(FGPIOC,3)) );
     }
  }
    
  // Kiem tra nut bam 2 - bam thi nhay vao firmware 2
    if ( 0 ==  (GPIO_ReadPin(FGPIOC,12)) )
  {
     Systick_Delay(0.2);
     if ( 0 ==  (GPIO_ReadPin(FGPIOC,12)) )
     {
        Jump_To_App(FIRAMWARE2_START_ADD);
        while( 0 ==  (GPIO_ReadPin(FGPIOC,12)) );
     }
  }
    
}


