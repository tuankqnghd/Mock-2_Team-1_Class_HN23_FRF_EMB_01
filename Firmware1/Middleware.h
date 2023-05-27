#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Clock.h"
#include "Port.h"
#include "GPIO.h"
/********************************************************************
 * API
********************************************************************/



/*
* @brief config for Systick 
*
*@return void
*/
void Systick_Init(void);



/*
* @brief delay 200ms
*
*@return void
*/
void SysDelay_200ms(void);



/*
* @brief config for RED Led of MKL46Z4
*
*@return void
*/
void RED_LED_Init(void);



/*
* @brief config for BLUE Led of MKL46Z4
*
*@return void
*/
void BLUE_LED_Init(void);



/*
* @brief config for button 1 of MKL46Z4
*
*@return void
*/
void BTN1_Init(void);



/*
* @brief blink mode: Green and Red Led blink concurrent with T = 200ms
*
*@return void
*/
void LED_Blink_Mode(void);



/*
* @brief flash mode: Green Led and Red Led flash with the cycle T = 200ms 
* (Green Led on while Red Led off)
*
*@return void
*/
void LED_Flash_Mode(void);



/*
* @brief read logic input of button 1
*
*@return input logic of button 1: 0 is logic 0, 1 is logic 1
*/
uint8_t READ_BTN1();



#endif