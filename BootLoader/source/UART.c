/*
* @file UART.c
* @brief UART lib support config for UART, call back funtion for UART interupt handler
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "UART.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static UART_ISRType sCallback_UART;

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

void UART_Init(UART_ConfigType * UserConfig)
{
  // Config Mode type
  UART0->C1 |= UART0_C1_M(UserConfig->Mode);
  
  // Config Parity Type
  UART0->C1 &= ~UART0_C1_PE_MASK;
  UART0->C1 &= ~UART0_C1_PT_MASK;
  if ((UserConfig->Parity == UART_PARITY_EVEN) || (UserConfig->Parity == UART_PARITY_ODD))
  {
    UART0->C1 |= UART0_C1_PE_MASK;
  }
  if (UserConfig->Parity == UART_PARITY_ODD)
  {
    UART0->C1 |= UART0_C1_PT_MASK;
  }
  
  // Config Stop bit
  UART0->BDH |= UART0_BDH_SBNS(UserConfig->Stopbit);
  
  // Config OSR
  UART0->C4 = UART0->C4 & ~UART0_C4_OSR_MASK | UART0_C4_OSR(UserConfig->OSR - 1);
  
  // Config SBR
  UART0->BDH &= ~UART0_BDH_SBR_MASK;
  UART0->BDL &= ~UART0_BDL_SBR_MASK;
  UART0->BDH |= UART_BDH_SBR((UserConfig->SBR) >> 8);
  UART0->BDL |= UART_BDL_SBR((uint8_t)(UserConfig->SBR));
  
  // Config interrupt 
  UART0->C2 |= (UART_C2_TIE(UserConfig->TIEINT) | UART_C2_RIE(UserConfig->TCIEINT) | UART_C2_RIE(UserConfig->RIEINT));
  
  // Callback funtion
  sCallback_UART = UserConfig->Callback;
  
  // Config Both Edge
  if ((UserConfig->OSR >= 4) && (UserConfig->OSR <= 7))
  {
    UART0->C5 |= UART0_C5_BOTHEDGE(1u);
  }
}



void UART0_IRQHandler(void)
{
  // Check interupt type
  if ((UART0->S1 & UART0_S1_RDRF_MASK) != 0)
  {
    // Clear flag
    UART0->S1 &= ~UART0_S1_RDRF_MASK;
  }
  
  // Callback funtion
  (*sCallback_UART)();
}



void UART_SendChar(uint8 Data)
{
  // Enable Transmit 
  UART0->C2 |= UART0_C2_TE(1u);

  // Wait buffer is empty - TDRE = 1
  while ((UART0->S1 & UART_S1_TDRE_MASK) == 0);
  
  // Write Data -> Data Register
  UART0->D = Data;
  
  // Wait transmit complete
  while ((UART0->S1 & UART0_S1_TC_MASK) == 0); 
  
  // Disable Transmit 
  UART0->C2 &= ~UART0_C2_TE_MASK;
}



void UART_SendUint32(uint32 Data)
{
  UART_SendChar((uint8)(Data >> 24));
  UART_SendChar((uint8)(Data >> 16));
  UART_SendChar((uint8)(Data >> 8));
  UART_SendChar((uint8)(Data >> 0));
}



void UART_SendString(char * String, uint8 len)
{
  uint8 i;
  
  // Enable Transmit 
  UART0->C2 |= UART0_C2_TE(1u);
  
  for (i = 0; i < len; i++)
  {
    // Wait buffer is empty - TDRE = 1
    while ((UART0->S1 & UART_S1_TDRE_MASK) == 0);
  
    // Write Data -> Data Register
    UART0->D = String[i]; //*(String + i)
  }
  // Wait transmit complete
  while ((UART0->S1 & UART0_S1_TC_MASK) == 0); 
  
  // Disable Transmit 
  UART0->C2 &= ~UART0_C2_TE_MASK;
}
    
    
    
uint8 UART_Receive()
{
  uint8_t Data;
  // Enable Receive
  UART0->C2 |= UART0_C2_RE(1u);
  
  // Wait Data buffer Full - RDRF = 1
  while ((UART0->S1 & UART0_S1_RDRF_MASK) == 0);
  
  // Read data from buffer
  Data = UART0->D;
  
  // Disale Receive
  UART0->C2 &= ~UART0_C2_RE_MASK;
  
  return Data;
}
