#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

/********************************************************************
 * Include Library
********************************************************************/

#include "MKL46Z4.h"
#include "Port.h"
#include "GPIO.h"
#include "UART.h"
#include "PIT.h"
#include "Flash.h"
#include "queue.h"
#include "types.h"

/********************************************************************
 * API
********************************************************************/

/*
* @brief copy vector table to RAM and set VTOR to new vector table
*
*@return void
*/
void Copy_Vector_Table_SetVTOR(void);



/*
* @brief return VTOR to 0x00000000
*
*@return void
*/
void ReturnVTOR(void);



///*
//* @brief config for RED Led of MKL46Z4
//*
//*@return void
//*/
//void RED_LED_Config(void);



///*
//* @brief config for BLUE Led of MKL46Z4
//*
//*@return void
//*/
//void BLUE_LED_Config(void);



/*
* @brief config for button 1 & 2 of MKL46Z4
*
*@return void
*/
void BTN_Config(void);



/*
* @brief read logic input of button 1
*
*@return input logic of button 1: 0 is logic 0, 1 is logic 1
*/
uint8 READ_BTN1();



/*
* @brief read logic input of button 2
*
*@return input logic of button 2: 0 is logic 0, 1 is logic 1
*/
uint8 READ_BTN2();



/*
* @brief config for PIT 
*
*@return void
*/
void PIT_Config_5s();



/*
* @brief config for UART
*
*@return void
*/
void UART_User_Config();



/*
* @brief covert char to hex
*
*@return hex
*/
uint8 ChartoHex(char c);

void FirmwaretoFlash(void);

void myUART_Handler();

#endif /* __MIDDLEWARE_H__ */