#ifndef __CLOCK_H__
#define __CLOCK_H_

/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"

/********************************************************************
 * API
********************************************************************/

typedef enum
{
  CLOCK_SOURCE_FLL_PLL  = 0u,
  CLOCK_SOURCE_INTERNAL = 1u,
  CLOCK_SOURCE_EXTERNAL = 2u,
  CLOCK_SOURCE_RESERVED = 3u,
} Clock_Source_Type;

typedef enum
{
  OUTDIV1_01            = 0u,
  OUTDIV1_02            = 1u,
  OUTDIV1_03            = 2u,
  OUTDIV1_04            = 3u,
  OUTDIV1_05            = 4u,
  OUTDIV1_06            = 5u,
  OUTDIV1_07            = 6u,
  OUTDIV1_08            = 7u,
  OUTDIV1_09            = 8u,
  OUTDIV1_10            = 9u,
  OUTDIV1_11            = 10u,
  OUTDIV1_12            = 11u,
  OUTDIV1_13            = 12u,
  OUTDIV1_14            = 13u,
  OUTDIV1_15            = 14u,
  OUTDIV1_16            = 15u,
} OUTDIV1_Number;

//.........

typedef struct
{
  Clock_Source_Type     clock_type;
  OUTDIV1_Number        outdiv1;
  // .........
} Clock_ConfigType;




/*
* @brief core clock config
*
*@param User_Config is a user struct
*
*@return void
*/
void Clock_Init(const Clock_ConfigType* User_Config);




#endif