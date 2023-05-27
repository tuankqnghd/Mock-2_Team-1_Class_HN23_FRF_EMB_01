/*
* @file LedBlinking.c
* @brief LedBlinking.c
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"

typedef unsigned int uint32;
typedef unsigned char uint8;

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



void Flash_WriteWord( uint32 address, uint32 data)
{
  // Wait previous command complete
  while ((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0);
  
  // Clear old error
  // Check 2 flag
  FTFA->FSTAT = 0x30;
  
  // Write parameter to FCCOB
  FTFA->FCCOB0 = 0x06;
  
  FTFA->FCCOB1 = (uint8)(address >> 16);
  FTFA->FCCOB2 = (uint8)(address >> 8);
  FTFA->FCCOB3 = (uint8)address;
  
  FTFA->FCCOB4 = (uint8)(data >> 24);
  FTFA->FCCOB5 = (uint8)(data >> 16);
  FTFA->FCCOB6 = (uint8)(data >> 8);
  FTFA->FCCOB7 = (uint8)data;
    
  // Clear the CCIF to launch
  FTFA->FSTAT = 0x80;
}



void Flash_EraseSector(uint32 address)
{
  // Sector 1 - 0x400-0x7FF
  if ((address >= 0x400u) && (address <0x7FFu))
  {
    return;
  }
    
  // Wait previous command complete
  while ((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0);
  
  // Clear old error
  // Check 2 flag
  FTFA->FSTAT = 0x30;
  
  // Write parameter to FCCOB
  FTFA->FCCOB0 = 0x09;
  
  // Tranfer address
  FTFA->FCCOB1 = (uint8)(address >> 16);
  FTFA->FCCOB2 = (uint8)(address >> 8);
  FTFA->FCCOB3 = (uint8)address;
  
  // Clear the CCIF to launch
  FTFA->FSTAT = 0x80;
}



uint32 Flash_Read(uint32 address)
{
  return *(uint32 *) address;
}



void main()
{
  volatile uint32 readdata;
  
  __disable_irq();
  
  __enable_irq();
  
  // Read from Flash
  readdata = *(uint32 *)0x00000000u;
  
  Flash_WriteWord(0x01FFF0u, readdata);
  Flash_WriteWord(0x01FFE0u, readdata);
  Flash_WriteWord(0x01FFD0u, readdata);
  Flash_WriteWord(0x01FFC0u, readdata);
  readdata = *(uint32 *)0x0001FFF0u;
  Flash_EraseSector(0x0001FFF0u);

  while(1)
  {

  }
}