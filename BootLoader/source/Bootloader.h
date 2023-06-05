#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#include "MKL46Z4.h"
# include "Middleware.h"


typedef unsigned int uint32;
typedef unsigned char uint8;


volatile uint8 ModeSelection = 0;

typedef enum
{
  DEFUALT               = 0u,
  BOOTLOADER_MODE       = 1u,
  FIRNWARE_MODE         = 2u,
}Run_Mode_type;

void LedGreen_INTConfig(void);

void Dis_Intterupt_Timer(void);

void Dis_Fault_Hander(void);

void Jump_To_App(uint32 Add) ;

void Firmware_Selection(void);


#endif