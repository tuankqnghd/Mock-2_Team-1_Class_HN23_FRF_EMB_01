/*
* @file Clock.c
* @brief Clock lib support user config core clock by config MCG, SIM, SMC module
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Clock.h"

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

void Clock_Init(const Clock_ConfigType* User_Config)
{
  // Check clock source type
  if ((User_Config->clock_type) > CLOCK_SOURCE_RESERVED)
  {
    return;
  }
  
  // Check pull type
  if ((User_Config->outdiv1) > OUTDIV1_16)
  {
    return;
  }
  
  // Select clock source type
  MCG->C1 &= ~MCG_C1_CLKS_MASK;
  MCG->C1 |= MCG_C1_CLKS(User_Config->clock_type);
  
  // Outdiv1
  SIM->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV1_MASK;
  SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(User_Config->outdiv1);
}
