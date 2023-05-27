/*
* @file TempSensor.c
* @brief TempSensor.c support read temperature of enviroment by Internal Temperature Sensor in
KL46
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "math.h"
#include "Middleware.h"

/********************************************************************
 * Definition
********************************************************************/

#define V_TEMP25          0.716
#define M_TEMP            0.00175
#define V_REF             3.3
#define ADC_RESOLUTION    16

/*********************************************************************
* Variable
*********************************************************************/

volatile uint16_t ADC_data;

volatile float Temp_value;

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

float Temperature_Cal(uint16_t ADC_value);

float Temperature_Cal(uint16_t ADC_value)
{
  return (25 - ((float)ADC_value / (pow(2, 16) - 1) * V_REF - V_TEMP25) / M_TEMP);
}


void myTimer_Handler(uint8_t Channel)
{
  if (Channel == 0)
  {
    // Toggle Green LED
    Toggle_GREEN_LED();
    
    // Trigger for ADC conversion
    ADC_Trigger_Conversion(ADC_CHANNEL_A, 26);
  }
  if (Channel == 1)
  {
    
  }
}

void myADC_Handler()
{
  // Toggle Red LED
  Toggle_RED_LED();
  
  // Read data ADC
  ADC_data = ADC0_Read(ADC_CHANNEL_A);
  Temp_value = Temperature_Cal(ADC_data);
}

PIT_ConfigType UserConfig_PIT = {
  .Channel      = PIT_CHANNEL_0,
  .FreezeMode   = PIT_MODE_RUN,
  .IntEnable    = PIT_INTERRUPT_ENABLE,
  .PeriodTime   = 500,  // 500ms
  .Callback     = &myTimer_Handler,
};

ADC_ConfigType UserConfig_ADC = {
  .Channel      = ADC_CHANNEL_A,
  .Clock        = ADC_CLOCK_BUSCLK,
  .Vref         = ADC_VREF_VREFH_VREFL,
  .Mode         = ADC_MODE_SINGLE_END,
  .Resolution   = ADC_RESOLUTION_16BIT,
  .EnableINT    = ADC_INT_ENABLE,
  .Callback     = &myADC_Handler,
};

void main()
{
  // Config for Red & Green LED
  RED_LED_Init();
  BLUE_LED_Init();
  
  // Config for PIT
  PIT_Init(&UserConfig_PIT);
  NVIC_EnableIRQ(PIT_IRQn);
  NVIC_SetPriority(PIT_IRQn, 2);
  
  // Config for ADC
  ADC_Init(&UserConfig_ADC);
  NVIC_EnableIRQ(ADC0_IRQn);
  NVIC_SetPriority(ADC0_IRQn, 1);
  
  // Start PIT
  PIT_TimerControl(PIT_CHANNEL_0, 1);
  
  while(1)
  {

  }
}