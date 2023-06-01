#ifndef __UART_H__
#define __UART_H__

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "types.h"

/********************************************************************
 * API
********************************************************************/

typedef void (*UART_ISRType)(void);

/* User defined data types */
typedef enum
{
  UART_MODE_8BIT        = 0u,
  UART_MODE_9BIT        = 1u,
} UART_ModeType;

typedef enum
{
  UART_PARITY_DISABLE   = 0u,
  UART_PARITY_EVEN      = 2u,
  UART_PARITY_ODD       = 3u,
} UART_ParityType;

typedef enum
{
  UART_STOPBIT_ONE      = 0u,
  UART_STOPBIT_TWO      = 1u,
} UART_StopbitType;

typedef enum
{
  UART_TIEINT_DISABLE   = 0u, 
  UART_TIEINT_ENABLE    = 1u, 
} UART_TIEINTType;

typedef enum
{
  UART_TCIEINT_DISABLE   = 0u, 
  UART_TCIEINT_ENABLE    = 1u, 
} UART_TCIEINTType;

typedef enum
{
  UART_RIEINT_DISABLE   = 0u, 
  UART_RIEINT_ENABLE    = 1u, 
} UART_RIEINTType;

// ... Error INT

typedef struct
{
  UART_ModeType         Mode;
  UART_ParityType       Parity;
  UART_StopbitType      Stopbit;
  uint8_t               OSR; 
  uint32_t              SBR;
  UART_TIEINTType       TIEINT;
  UART_TCIEINTType      TCIEINT;
  UART_RIEINTType       RIEINT;
  UART_ISRType          Callback;
} UART_ConfigType;

/* Function Prototypes */

/*
* @brief config UART
*
*@param UART_ConfigType is a struct with user parameter
*
*@return void
*/
void UART_Init(UART_ConfigType * UserConfig);



/*
* @brief send a char by UART
*
*@param Data is a char
*
*@return void
*/
void UART_SendChar(uint8 Data);



/*
* @brief send string by UART
*
*@param String is adress of string need to send
*
*@return void
*/
void UART_SendString(char * String, uint8 len);



/*
* @brief receive data by UART
*
*@return data
*/
uint8 UART_Receive();



#endif /* __UART_H__ */
