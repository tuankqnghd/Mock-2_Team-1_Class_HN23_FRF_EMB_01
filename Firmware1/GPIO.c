/*
* @file GPIO.c
* @brief GPIO lib support config IO for GPIO, set, clear, toggle, read a pin funtion
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "GPIO.h"

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



void GPIO_Init(GPIO_Type * GPIOx, uint8_t pin, GPIO_IO_Type IO_Type)
{
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  // Check IO type
  if (IO_Type > GPIO_IO_OUTPUT)
  {
    return;
  }
  
  // Select I/O
  if (IO_Type == GPIO_IO_OUTPUT) 
  {
    GPIOx->PDDR |= (1 << pin); // Set pin direction to output
  } 
  else if (IO_Type == GPIO_IO_INPUT) 
  {
    GPIOx->PDDR &= ~(1 << pin); // Set pin direction to input
  }
}



void GPIO_SetPin (FGPIO_Type * FGPIOx, uint8_t pin)
{
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  FGPIOx->PSOR |= (1 << pin);
}



void GPIO_ClearPin (FGPIO_Type * FGPIOx, uint8_t pin)
{
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  FGPIOx->PCOR |= (1 << pin);
}



void GPIO_TogglePin (FGPIO_Type * FGPIOx, uint8_t pin)
{
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  FGPIOx->PTOR |= (1 << pin);
}



uint8_t GPIO_ReadPin (FGPIO_Type * FGPIOx, uint8_t pin)
{
  // Check pin number
  if (pin > 31) 
  {
    return 2;
  }
  
  return (FGPIOx->PDIR >> pin) & 1;
}