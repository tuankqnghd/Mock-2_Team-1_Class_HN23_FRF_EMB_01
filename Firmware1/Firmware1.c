/*
* @file LedBlinking.c
* @brief LedBlinking.c support do blink mode and flash mode for 2 led of MKL46Z4
* switch mode by button 1 
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Middleware.h"

/********************************************************************
 * Definition
********************************************************************/
#define MODE_BLINK (1)
#define MODE_FLASH (2)

/*********************************************************************
* Variable
*********************************************************************/
typedef unsigned int uint32;
typedef unsigned char uint8;

volatile uint8 mode = MODE_BLINK;

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

void PORTC_PORTD_IRQHandler(void)
{
  // Check if interupt from Port C.3 
  if ((PORTC->ISFR & (1 << 3)) != 0)
  {
    // Clear ISF flag
    PORT_EXTI_ClearFlag (PORTC, 3);
  
    // Delay for debouncing
    uint32 count = 4000;
    while(--count);

    // Check button state
    if (READ_BTN1() == 0) 
    {
      if (mode == MODE_BLINK) 
      {
        mode = MODE_FLASH;
      } 
      else 
      {
        mode = MODE_BLINK;
      }
    }
  }
}



void main()
{
  Systick_Init_100ms();
  
  // Config Red Led
  RED_LED_Init();
  
  // Config Blue Led
  BLUE_LED_Init();
  
  // Setup Button SW1
  BTN1_Init();

  // Setup interupt for Port C & Port D, priority lever = 0
  PORT_EXTI_Config(PORTC_PORTD_IRQn, 0);
 
  while(1)
  {
    if (mode == MODE_BLINK)
    {
      LED_Blink_Mode();
    }
    else if (mode == MODE_FLASH)
    {
      LED_Flash_Mode();
    }
  }
}