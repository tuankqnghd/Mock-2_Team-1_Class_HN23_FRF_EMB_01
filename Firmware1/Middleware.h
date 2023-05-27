#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Port.h"
#include "GPIO.h"
#include "PIT.h"
/********************************************************************
 * API
********************************************************************/



/*
* @brief config for RED Led of MKL46Z4
*
*@return void
*/
void RED_LED_Config(void);



/*
* @brief config for BLUE Led of MKL46Z4
*
*@return void
*/
void BLUE_LED_Config(void);



/*
* @brief config for button 1 of MKL46Z4
*
*@return void
*/
void BTN1_Config(void);



/*
* @brief read logic input of button 1
*
*@return input logic of button 1: 0 is logic 0, 1 is logic 1
*/
uint8_t READ_BTN1(void);



/*
* @brief config for PIT channel 0 & channel 1 of MKL46Z4
*
*@return void
*/
void PIT_Config_LED_Blink(void);



#endif