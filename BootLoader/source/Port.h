#ifndef __PORT_H__
#define __PORT_H__

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "types.h"

/********************************************************************
 * API
********************************************************************/

typedef enum
{
  PULL_DISABLE          = 0u,
  PULL_DOWN             = 2u,
  PULL_UP               = 3u,
} Port_Pull_Type;

typedef enum
{
  PORT_IRQ_DISABLE      = 0x0u,
  PORT_DMA_EDGE_RISING  = 0x1u,
  PORT_DMA_EDGE_FALLING = 0x2u,
  PORT_DMA_EDGE_EITHER  = 0x3u,
  PORT_IRQ_LOGIC_ZERO   = 0x8u,
  PORT_IRQ_EDGE_RISING  = 0x9u,
  PORT_IRQ_EDGE_FALLING = 0xAu,
  PORT_IRQ_EDGE_EITHER  = 0xBu,
  PORT_IRQ_LOGIC_ONE    = 0xCu,
} Port_IRQType;

typedef enum
{
  PORT_MUX_ANALOG       = 0x0u,
  PORT_MUX_GPIO         = 0x1u,
  PORT_MUX_ALT2         = 0x2u,
  PORT_MUX_ALT3         = 0x3u,
  PORT_MUX_ALT4         = 0x4u,
  PORT_MUX_ALT5         = 0x5u,
  PORT_MUX_ALT6         = 0x6u,
  PORT_MUX_ALT7         = 0x7u,  
} Port_MuxType;

typedef struct
{
  Port_MuxType          Mux;
  Port_Pull_Type        pull;
  Port_IRQType          IRQ;
} Port_ConfigType;

  
  
/*
* @brief config GPIO
*
*@param PORTx is PORT_Type of PORT need to config
*@param pin is pin number of pin need to config
*@param UserConfig is a struct with user parameter
*
*@return void
*/
void PORT_Init(PORT_Type * PORTx, uint8 pin, const Port_ConfigType* UserConfig);



/*
* @brief config interupt for PORT
*
*@param IRQn is IRQn_Type need to config
*@param priority_lever is priority lever of interupt line
*
*@return void
*/
void PORT_EXTI_Config(IRQn_Type IRQn, uint8 priority_lever);



/*
* @brief clear ISFR flag for a pin of PORT
*
*@param PORTx is PORT_Type of PORT need to clear ISFR flag
*@param pin is pin number of pin need to config
*
*@return void
*/
void PORT_EXTI_ClearFlag (PORT_Type * PORTx, uint8 pin);



#endif /* __PORT_H__ */