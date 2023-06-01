/*
* @file Port.c
* @brief Port lib support config for PORT, setup interupt for a PORT, clear ISFR flag for a pin of PORT
*/
/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "Port.h"

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

void PORT_Init(PORT_Type * PORTx, uint8 pin,const Port_ConfigType* UserConfig)
{ 
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  // Check pull type
  if ((UserConfig->pull) > PULL_UP)
  {
    return;
  }
  
  // Check mux type
  if ((UserConfig->Mux) > PORT_MUX_ALT7)
  {
    return;
  }
  
  // Check IRQ
  if ((UserConfig->IRQ) > PORT_IRQ_LOGIC_ONE)
  {
    return;
  }
  
  /* Multiplexing */
  PORTx->PCR[pin] &= ~PORT_PCR_MUX_MASK;
  PORTx->PCR[pin] |= PORT_PCR_MUX(UserConfig->Mux);
  
  /* Pull Control */
  PORTx->PCR[pin] &= ~PORT_PCR_PE_MASK;
  PORTx->PCR[pin] &= ~PORT_PCR_PS_MASK;
  if ((UserConfig->pull == PULL_DOWN) || (UserConfig->pull == PULL_UP))
  {
    PORTx->PCR[pin] |= PORT_PCR_PE(1);
  }
  if (UserConfig->pull == PULL_UP)
  {
    PORTx->PCR[pin] |= PORT_PCR_PS(1);
  }
  
  // Pin Interrupt
  PORTx->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
  PORTx->PCR[pin] |= PORT_PCR_IRQC(UserConfig->IRQ);
}



void PORT_EXTI_Config(IRQn_Type IRQn, uint8_t priority_lever)
{
  // Check priority lever
  if (priority_lever > 15) 
  {
    return;
  }
  
  // Config NVIC
  NVIC_SetPriority(IRQn, priority_lever);  // Set Priority
  NVIC_ClearPendingIRQ(IRQn);              // Clear Pending Interrupt
  NVIC_EnableIRQ(IRQn);                    // Enable Interrupt 
}



void PORT_EXTI_ClearFlag (PORT_Type * PORTx, uint8 pin)
{
  // Check pin number
  if (pin > 31) 
  {
    return;
  }
  
  // Check if the flag is set
  if ((PORTx->ISFR & (1 << pin)) != 0) 
  {
    // If flag is set, clear the flag
    PORTx->ISFR |= (1 << pin);
  }
}

