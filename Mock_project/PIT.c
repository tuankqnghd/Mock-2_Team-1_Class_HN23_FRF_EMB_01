/*
* @file PIT.c
* @brief PIT lib support config for PIT, call back funtion for PIT interupt handler
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "PIT.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static PIT_ISRType sCallback_PIT;

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

static void PIT_ClearInterruptFlag(PIT_ChannelType CHAN);

/*********************************************************************
* Global function 
*********************************************************************/

void PIT_Init(PIT_ConfigType * UserConfig)
{
    uint32_t LoadValue = 0;
    
    // Enable Clock for PIT
    SIM->SCGC6 |= (1 << 23);
    
    // Turn on PIT
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;       // Always

    // Set freemode(if need)
    if ( PIT_MODE_RUN == UserConfig->FreezeMode )
    {
      PIT->MCR &= ~PIT_MCR_FRZ_MASK;
    }
    else
    {
      PIT->MCR |= PIT_MCR_FRZ(1);
    }
    
    // Setup Reload Value - Period Time (100ms)
    // SystemCoreClock = Core Clock
    // PIT = Bus Clock = Core Clock / OUTDIV4 (SIM_CLKDIV1)
    // PIT clock frequency = SystemCoreClock / (OUTDIV4 + 1)
    // PIT clock period = (OUTDIV4 + 1) / SystemCoreClock
    // LDVAL trigger = (period / PIT clock period) -1
    SystemCoreClockUpdate();
    LoadValue = (UserConfig->PeriodTime * (SystemCoreClock/1000u/BUS_CLOCK_DIV)) - 1u;
    PIT->CHANNEL[UserConfig->Channel].LDVAL = LoadValue;

    // Setup Interrupt if need
    if (PIT_INTERRUPT_ENABLE == UserConfig->IntEnable)
    {
      PIT->CHANNEL[UserConfig->Channel].TCTRL |= PIT_TCTRL_TIE(1);
      sCallback_PIT = UserConfig->Callback;
    }
    else
    {
      PIT->CHANNEL[UserConfig->Channel].TCTRL &= ~PIT_TCTRL_TIE_MASK;
    }
}



void PIT_TimerControl(PIT_ChannelType Channel, uint8_t EnorDis)
{
  if ( 0 == EnorDis )
  {
    // Stop Timer
    PIT->CHANNEL[Channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
  }
  else
  {
    // Start Timer
    PIT->CHANNEL[Channel].TCTRL |= PIT_TCTRL_TEN(1);
  }
}



void PIT_IRQHandler(void) //  Driver Code
{  
  if ((PIT->CHANNEL[0].TFLG & (1 << 0)) != 0)
  {
    (*sCallback_PIT)(PIT_CHANNEL_0);
    
    // Clear interrupt flag for channel 0
    PIT_ClearInterruptFlag(PIT_CHANNEL_0);
  }
  if ((PIT->CHANNEL[1].TFLG & (1 << 0)) != 0)
  {
    (*sCallback_PIT)(PIT_CHANNEL_1);
    
    // Clear interrupt flag for channel 1
    PIT_ClearInterruptFlag(PIT_CHANNEL_1);
  }
}



void PIT_ClearInterruptFlag(PIT_ChannelType CHAN)
{
  PIT->CHANNEL[CHAN].TFLG |= (1 << 0);
}
