/*
* @file Middleware.c
* @brief Middleware lib support user config to red, blue led, button 1, read input logic button 1 of MKL46Z4
* config core clock and delay 200ms funtion 
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Middleware.h"

/********************************************************************
 * Definition
********************************************************************/

#define MODE_BLINK             (1)
#define MODE_FLASH             (2)

typedef unsigned int uint32;
typedef unsigned char uint8;

/*********************************************************************
* Variable
*********************************************************************/

volatile uint8 mode = MODE_FLASH;

volatile uint8 LED_status = 0;

void myTimer_Handler(uint8_t Channel);

const Port_ConfigType  UserConfig_PortC3 = {
  .Mux = PORT_MUX_GPIO, 
  .pull = PULL_UP,
  .IRQ = PORT_IRQ_EDGE_FALLING,
};

const Port_ConfigType  UserConfig_PortD5 = {
  .Mux = PORT_MUX_GPIO, 
};

const Port_ConfigType  UserConfig_PortE29 = {
  .Mux = PORT_MUX_GPIO, 
};

PIT_ConfigType UserConfig_PIT_CHANNEL_0 = {
  .Channel      = PIT_CHANNEL_0,
  .FreezeMode   = PIT_MODE_RUN,
  .IntEnable    = PIT_INTERRUPT_ENABLE,
  .PeriodTime   = 200,  // 200ms
  .Callback     = &myTimer_Handler,
};

PIT_ConfigType UserConfig_PIT_CHANNEL_1 = {
  .Channel      = PIT_CHANNEL_1,
  .FreezeMode   = PIT_MODE_RUN,
  .IntEnable    = PIT_INTERRUPT_ENABLE,
  .PeriodTime   = 100,  // 100ms
  .Callback     = &myTimer_Handler,
};

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/



void PORTC_PORTD_IRQHandler(void)
{
  // Check if interupt from Port C.3 
  if ((PORTC->ISFR & (1 << 3)) != 0)
  {
    // Clear ISF flag
    PORT_EXTI_ClearFlag (PORTC, 3);
  
    // Delay for debouncing
    uint32 count = 4000;
    while(--count);

    // Check button state
    if (READ_BTN1() == 0) 
    {
      if (mode == MODE_BLINK) 
      {
        mode = MODE_FLASH;
        PIT_TimerControl(PIT_CHANNEL_0, 0);
        PIT_TimerControl(PIT_CHANNEL_1, 1);
      } 
      else if (mode == MODE_FLASH)
      {
        mode = MODE_BLINK;
        PIT_TimerControl(PIT_CHANNEL_0, 1);
        PIT_TimerControl(PIT_CHANNEL_1, 0);
      }
    }
  }
}



void myTimer_Handler(uint8_t Channel)
{
  if (Channel == 0) // Blink mode
  {
    if (LED_status == 0)
    {
      // Turn on both of 2 lED
      GPIO_ClearPin(FGPIOE, 29);
      GPIO_ClearPin(FGPIOD, 5);
      
      LED_status = 1;
    }
    else if (LED_status == 1)
    {
      // Turn of both of 2 LED
      GPIO_SetPin(FGPIOE, 29);
      GPIO_SetPin(FGPIOD, 5);
      
      LED_status = 0;
    }
  }
  if (Channel == 1) // Flash mode
  {
    if (LED_status == 0)
    {
      // Turn on red led, turn of blue led
      GPIO_ClearPin(FGPIOE, 29);
      GPIO_SetPin(FGPIOD, 5);
      
      LED_status = 1;
    }
    else if (LED_status == 1)
    {
      // Turn off red led, turn on blue led
      GPIO_SetPin(FGPIOE, 29);
      GPIO_ClearPin(FGPIOD, 5);
      
      LED_status = 0;
    }
  }
}



void RED_LED_Config(void)
{
  // Enable clock for PORTE, GPIOE
  SIM->SCGC5 |= SIM_SCGC5_PORTE(1);  
  
  // Config Port E
  PORT_Init(PORTE, 29, &UserConfig_PortE29);
  
  // PinE.29 = Output
  GPIO_Init(GPIOE, 29, GPIO_IO_OUTPUT);
}



void BLUE_LED_Config(void)
{
  // Enable clock for PORTD, GPIOD
  SIM->SCGC5 |= SIM_SCGC5_PORTD(1);  
  
  // Config Port D
  PORT_Init(PORTD, 5, &UserConfig_PortD5);
  
  // PinD.5 = Output
  GPIO_Init(GPIOD, 5, GPIO_IO_OUTPUT);
}



void BTN1_Config(void)
{
  // Enable Clock for Port C
  SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
  
  // Config Port C
  PORT_Init(PORTC, 3, &UserConfig_PortC3);
  
  // PinC.3 = Input
  GPIO_Init(GPIOC, 3, GPIO_IO_INPUT);
  
  // Setup interupt for Port C & Port D, priority lever = 0
  PORT_EXTI_Config(PORTC_PORTD_IRQn, 0);
}



uint8_t READ_BTN1(void)
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}



void PIT_Config_LED_Blink(void)
{
  PIT_Init(&UserConfig_PIT_CHANNEL_0);
  
  PIT_Init(&UserConfig_PIT_CHANNEL_1);
  
  // Enable Interupt
  NVIC_EnableIRQ(PIT_IRQn);
  
  // Set Priority
  NVIC_SetPriority(PIT_IRQn, 1);
}


