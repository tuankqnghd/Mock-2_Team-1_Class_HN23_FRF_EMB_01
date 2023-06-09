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
* @brief erase flash memory for load firmware to flash
*
*@return void
*/
void Erase_Flash_Memory(void);
   


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
void BTN_Init(void);



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
* @brief config for Systick
*
*@return void
*/
void Systick_Init(void);



/*
* @brief delay ms by systick
*
*@param timedelay is time to delay (ms) 
*
*@return void
*/
void Systick_Delay_ms(uint32 timedelay);



/*
* @brief delay 5s by systick timer 
*
*@return void
*/
void Systick_Delay_5s(void);



/*
* @brief config for UART
*
*@return void
*/
void UART_User_Init();



/*
* @brief covert char to hex
*
*@param c is char need to convert to hex 
*
*@return hex
*/
uint8 ChartoHex(char c);



/*
* @brief load firmware to flash
*
*@return void
*/
void FirmwaretoFlash(void);



/*
* @brief disable all interupt
*
*@return void
*/
void Dis_Intterupt(void);
                         
                         
                         
/*
* @brief turn off Systick Timer
*
*@return void
*/
void Dis_SystickTimer(void);



/*
* @brief Clear  pending interupt request
*
*@return void
*/
void Dis_Fault_Hander(void);



/*
* @brief Jump to new firmware
*
*@param Add is address of firmware reset handler
*
*@return void
*/
void Jump_To_App(uint32 Add);



/*
* @brief select firmware to jump
*
*@return void
*/
void Mode_Selection (void);



#endif /* __MIDDLEWARE_H__ */