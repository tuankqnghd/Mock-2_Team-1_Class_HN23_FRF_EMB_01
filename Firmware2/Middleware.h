#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Port.h"
#include "GPIO.h"
#include "PIT.h"
#include "ADC.h"
#include "UART.h"
//#include "UART.h"
/********************************************************************
 * API
********************************************************************/



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
* @brief toggle status of Red LED
*
*@return void
*/
void Toggle_RED_LED(void);



/*
* @brief toggle status of Green LED
*
*@return void
*/
void Toggle_GREEN_LED(void);



/*
* @brief read logic input of button 1
*
*@return input logic of button 1: 0 is logic 0, 1 is logic 1
*/
uint8_t READ_BTN1();



/*
* @brief calculate temperature value by ADC value
*
* @param ADC_value is ADC read value of temperature sensor
*
*@return temperature value (Celsius) (C) 
*/
float Temperature_Cal(uint16_t ADC_value);

void PIT_Config_1s();

void ADC_TempSensor_Config();

void UART_User_Config();


#endif