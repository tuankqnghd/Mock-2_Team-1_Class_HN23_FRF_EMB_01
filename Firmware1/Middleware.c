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

/*********************************************************************
* Variable
*********************************************************************/
const Clock_ConfigType UserConfig_Clock = {
  .clock_type = CLOCK_SOURCE_EXTERNAL,
  .outdiv1 = OUTDIV1_08,
};

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

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/



void Systick_Init_100ms(void)
{
  // Configure Clock & Clock Source
  // Core Clock - 1MHz
  Clock_Init(&UserConfig_Clock);
    
  // Configure System timer
  SysTick->CTRL |= (1 << 2);
  SysTick->LOAD = 100000u; // 200ms
}



void SysDelay_100ms(void)
{
  // Start Counter - ENABLE
  SysTick->VAL = 0u;
  SysTick->CTRL |= (1 << 0);
    
  // Wait COUNTFLAG = 1
  while ((SysTick->CTRL & (1 << 16)) == 0 );
  SysTick->CTRL &= ~(1 << 0);
}



void SysDelay_200ms(void)
{
  SysDelay_100ms();
  SysDelay_100ms();
}



void RED_LED_Init(void)
{
  // Enable clock for PORTE, GPIOE
  SIM->SCGC5 |= SIM_SCGC5_PORTE(1);  
  
  // Config Port E
  PORT_Init(PORTE, 29, &UserConfig_PortE29);
  
  // PinE.29 = Output
  GPIO_Init(GPIOE, 29, GPIO_IO_OUTPUT);
}



void BLUE_LED_Init(void)
{
  // Enable clock for PORTD, GPIOD
  SIM->SCGC5 |= SIM_SCGC5_PORTD(1);  
  
  // Config Port D
  PORT_Init(PORTD, 5, &UserConfig_PortD5);
  
  // PinD.5 = Output
  GPIO_Init(GPIOD, 5, GPIO_IO_OUTPUT);
}



void BTN1_Init(void)
{
  // Enable Clock for Port C
  SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
  
  // Config Port C
  PORT_Init(PORTC, 3, &UserConfig_PortC3);
  
  // PinC.3 = Input
  GPIO_Init(GPIOC, 3, GPIO_IO_INPUT);
}



void LED_Blink_Mode(void)
{
  // Turn on
  GPIO_ClearPin(FGPIOE, 29);
  GPIO_ClearPin(FGPIOD, 5);
  
  // Delay 200ms
  SysDelay_200ms();
  
  // Turn off
  GPIO_SetPin(FGPIOE, 29);
  GPIO_SetPin(FGPIOD, 5);

  // Delay 200ms
  SysDelay_200ms();  
}



void LED_Flash_Mode(void)
{
  // Turn on red led, turn of blue led
  GPIO_ClearPin(FGPIOE, 29);
  GPIO_SetPin(FGPIOD, 5);
  
  // Delay 100ms
  SysDelay_100ms();
  
  // Turn off red led, turn on blue led
  GPIO_SetPin(FGPIOE, 29);
  GPIO_ClearPin(FGPIOD, 5);

  // Delay 100ms
  SysDelay_100ms();  
}



uint8_t READ_BTN1()
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}

