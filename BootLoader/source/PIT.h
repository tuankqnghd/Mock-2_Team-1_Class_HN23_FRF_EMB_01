#ifndef __PIT_H__
#define __PIT_H__

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "types.h"

/********************************************************************
 * API
********************************************************************/


/* Parameters
  - Freeze mode (True/False)
  - Period Time
  - Enable Interrupt
  - Timer Channel       - Specific
  - Chain Mode (Not used now)
*/

#define BUS_CLOCK_DIV   (uint8)(((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) +1)

typedef void (*PIT_ISRType)(uint8);

/* User defined data types */
typedef enum
{
  PIT_CHANNEL_0         = 0u,
  PIT_CHANNEL_1         = 1u,
} PIT_ChannelType;

typedef enum
{
  PIT_MODE_RUN          = 0u,
  PIT_MODE_FREEZE       = 1u,
} PIT_ModeType;

typedef enum
{
  PIT_INTERRUPT_DISABLE = 0u,
  PIT_INTERRUPT_ENABLE  = 1u,
} PIT_IntType;

typedef struct
{
  PIT_ChannelType       Channel;
  PIT_ModeType          FreezeMode;
  uint32_t              PeriodTime; // (ms)
  PIT_IntType           IntEnable;
  PIT_ISRType           Callback;
} PIT_ConfigType;

/* Function Prototypes */

/*
* @brief config PIT
*
*@param UserConfig is a struct with user parameter
*
*@return void
*/
void PIT_Init(PIT_ConfigType * UserConfig);



/*
* @brief start/stop PIT timer
*
*@param Channel is channel number (0 or 1)
*@param EnorDis: 0 if stop timer
*                1 if start timer
*
*@return void
*/
void PIT_TimerControl(PIT_ChannelType Channel, uint8 EnorDis);

#endif /* __PIT_H__ */
