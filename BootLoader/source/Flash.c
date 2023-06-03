/*
* @file Flash.c
* @brief Flash lib support 
*/
/********************************************************************
 * Include Library
********************************************************************/

#include "Flash.h"

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

void Flash_WriteWord(uint32 address, uint32 data)
{
  if ( (0x00000400 <= address) && (0x0000040F >= address))
  {
    return;
  }
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
  return *(uint32 *)address;
}



uint8 Flash_IsReady()
{
  return ((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) >> FTFA_FSTAT_CCIF_SHIFT);
}