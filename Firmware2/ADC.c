/*
* @file ADC.c
* @brief ADC lib support config for ADC, read ADC convert value
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "ADC.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static ADC_ISRType sCallback_ADC;

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

// Read Temperature Sensor - (Single - End 26) 

/* Configuration for ADC
  - Enable Peripheral Clock - SIM (Access Register)
  - Select channel A/B
  - Clock (Clocksoure) - Bus Clock - ADICLK / ADIV
  - Vontage Reference - VREFH - VREFL = 3V - SC2 - REFSEL
  - Resolution (Output mode) - Single End 16 bits - DIFF, MODE
  - Other configuration
*/

void ADC_Init(ADC_ConfigType * UserConfig)
{
  // Enable Clock for ADC0
  SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
  
  // Select Mux ADC channel A/B
  ADC0->CFG2 |= ADC_CFG2_MUXSEL(UserConfig->Channel);
  
  // Select Clockf for ADC
  ADC0->CFG1 &= ~ADC_CFG1_ADICLK_MASK;
  ADC0->CFG1 |= ADC_CFG1_ADICLK(UserConfig->Clock);
  
  // Select Vontage Reference for ADC
  ADC0->SC2 &= ~ADC_SC2_REFSEL_MASK;
  ADC0->SC2 |= ADC_SC2_REFSEL(UserConfig->Vref);
  
  // Select Mode for ADC
  ADC0->SC1[UserConfig->Channel] |= ADC_SC1_DIFF(UserConfig->Mode);
  
  // Select Resolution
  ADC0->CFG1 &= ~ADC_CFG1_MODE_MASK;
  ADC0->CFG1 |= ADC_CFG1_MODE(UserConfig->Resolution);
  
  // Enable INT
  ADC0->SC1[UserConfig->Channel] |= ADC_SC1_AIEN(UserConfig->EnableINT);
  if ((UserConfig->EnableINT) == ADC_INT_ENABLE)
  {
    sCallback_ADC = UserConfig->Callback;
  }
}



void ADC_Trigger_Conversion(ADC_ChannelType Channel, uint8_t AD_channel)
{
  // Start Conversion
  ADC0->SC1[Channel] = (ADC0->SC1[Channel] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(AD_channel);
}



void ADC0_IRQHandler(void)
{
  (*sCallback_ADC)();
}



uint16_t ADC0_Read(ADC_ChannelType channel)
{
  return ADC0->R[channel];
}
