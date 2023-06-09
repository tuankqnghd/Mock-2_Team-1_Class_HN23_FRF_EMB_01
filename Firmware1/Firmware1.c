/*
* @file LedBlinking.c
* @brief LedBlinking.c support do blink mode and flash mode for 2 led of MKL46Z4
* switch mode by button 1 
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

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

void main()
{
  // Config Red Led
  RED_LED_Config();
  
  // Config Blue Led
  BLUE_LED_Config();
  
  // Setup Button SW1
  BTN1_Config();
  
  // Config for PIT
  PIT_Config_LED_Blink();
 
  while(1)
  {
  }
}