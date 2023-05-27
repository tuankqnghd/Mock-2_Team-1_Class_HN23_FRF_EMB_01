/*
* @file Firmware2.c
* @brief Firmware2.c support read temperature of enviroment by Internal Temperature Sensor in
KL46
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
  // Config for Red & Green LED
  RED_LED_Init();
  BLUE_LED_Init();
  
  // Config for PIT
  PIT_Config_1s();
  
  // Config for ADC
  ADC_TempSensor_Config();
  
  // UART Config
  UART_User_Config();
  
  // Start PIT
  PIT_TimerControl(PIT_CHANNEL_0, 1);
  
  while(1)
  {
    
  }
}