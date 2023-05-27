#ifndef __ADC_H__
#define __ADC_H__

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"

/********************************************************************
 * API
********************************************************************/

typedef void (*ADC_ISRType)(void);

/* User defined data types */
typedef enum
{
  ADC_CHANNEL_A         = 0u,
  ADC_CHANNEL_B         = 1u,
} ADC_ChannelType;

typedef enum
{
  ADC_CLOCK_BUSCLK      = 0u,
  ADC_CLOCK_BUSCLKDIV2  = 1u,
  ADC_CLOCK_ALTCLK      = 2u,
  ADC_CLOCK_ADACK       = 3u,
} ADC_ClockType;

typedef enum
{
  ADC_VREF_VREFH_VREFL = 0u,
  ADC_VREF_VALTH_VALTL = 1u,
  ADC_VREF_RESERVED1   = 2u,
  ADC_VREF_RESERVED2   = 3u, 
} ADC_VrefType;

typedef enum
{
  ADC_MODE_SINGLE_END  = 0u,
  ADC_MODE_DIFFRENTIAL = 1u,
} ADC_ModeType;

typedef enum
{
  ADC_RESOLUTION_8BIT  = 0u, // DIFF 9BIT
  ADC_RESOLUTION_12BIT = 1u, // DIFF 13BIT
  ADC_RESOLUTION_10BIT = 2u, // DIFF 11BIT
  ADC_RESOLUTION_16BIT = 3u, // DIFF 16BIT
} ADC_ResolutionType;

typedef enum
{
  ADC_INT_DISABLE      = 0u, 
  ADC_INT_ENABLE       = 1u, 
} ADC_INTType;

typedef struct
{
  ADC_ChannelType       Channel;
  ADC_ClockType         Clock;
  ADC_VrefType          Vref;
  ADC_ModeType          Mode;
  ADC_ResolutionType    Resolution;
  ADC_INTType           EnableINT;
  ADC_ISRType           Callback;
} ADC_ConfigType;




/* Function Prototypes */

/*
* @brief config ADC
*
*@param UserConfig is a struct with user parameter
*
*@return void
*/
void ADC_Init(ADC_ConfigType * UserConfig);




/*
* @brief trigger for ADC
*
*@param Channel is channel of ADC need to trigger (A/B)
*@param AD_channel is channel number of ADC need to trigger)
*
*@return void
*/
void ADC_Trigger_Conversion(ADC_ChannelType Channel, uint8_t AD_channel);



/*
* @brief config ADC
*
*@param Channel is channel of ADC need to trigger (A/B)
*
*@return void
*/
uint16_t ADC0_Read(ADC_ChannelType channel);

#endif /* __ADC_H__ */
