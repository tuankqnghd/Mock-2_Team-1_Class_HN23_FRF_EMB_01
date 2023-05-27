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



void Toggle_RED_LED(void)
{
  GPIO_TogglePin(GPIOE, 29);
}




void Toggle_GREEN_LED(void)
{
  GPIO_TogglePin(GPIOD, 5);
}



uint8_t READ_BTN1()
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}

