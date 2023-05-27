#ifndef __GPIO_H__
#define __GPIO_H__

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
/********************************************************************
 * API
********************************************************************/

typedef enum
{
  GPIO_IO_INPUT  = 0u,
  GPIO_IO_OUTPUT = 1u,
} GPIO_IO_Type;




/*
* @brief config IO for GPIOx
*
*@param GPIOx is GPIO_Type of GPIO need to config
*@param pin is pin number of pin need to config
*@param IO_Type: GPIO_IO_INPUT  = 0u; GPIO_IO_OUTPUT = 1u
*
*@return void
*/
void GPIO_Init(GPIO_Type * GPIOx, uint8_t pin, GPIO_IO_Type IO_Type);



/*
* @brief set output for a pin of GPIO
*
*@param FGPIOx is GPIO_Type of GPIO need to config
*@param pin is pin number of pin need to config
*
*@return void
*/
void GPIO_SetPin (FGPIO_Type * FGPIOx, uint8_t pin);



/*
* @brief clear output for a pin of GPIO
*
*@param FGPIOx is GPIO_Type of GPIO need to config
*@param pin is pin number of pin need to config
*
*@return void
*/
void GPIO_ClearPin (FGPIO_Type * FGPIOx, uint8_t pin);



/*
* @brief toggle output for a pin of GPIO
*
*@param FGPIOx is GPIO_Type of GPIO need to config
*@param pin is pin number of pin need to config
*
*@return void
*/
void GPIO_TogglePin (FGPIO_Type * FGPIOx, uint8_t pin);



/*
* @brief read input for a pin of GPIO
*
*@param FGPIOx is GPIO_Type of GPIO need to config
*@param pin is pin number of pin need to config
*
*@return logic input: 0 is logic 0; 1 is logic 1
*/
uint8_t GPIO_ReadPin (FGPIO_Type * FGPIOx, uint8_t pin);



#endif