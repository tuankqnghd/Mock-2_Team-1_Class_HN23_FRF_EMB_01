#ifndef __FLASH_H__
#define __FLASH_H__

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "types.h"

/********************************************************************
 * API
********************************************************************/

/* Function Prototypes */

/*
* @brief write work to flash memory
*
*@param address is address of flash need to write
*@param data is value need to write to flash memory
*
*@return void
*/
void Flash_WriteWord(uint32 address, uint32 data);



/*
* @brief write work to flash memory
*
*@param address is address of flash need to erase
*
*@return void
*/
void Flash_EraseSector(uint32 address);



/*
* @brief write work to flash memory
*
*@param address is address of flash need to read
*
*@return void
*/
uint32 Flash_Read(uint32 address);



uint8 Flash_IsReady();



#endif /* __FLASH_H__ */
