/*
* @file Middleware.c
* @brief Middleware lib support user config to red, blue led, button 1, read input logic button 1 of MKL46Z4, ...
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "Middleware.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static void myTimer_Handler(uint8_t Channel);

static void myUART_Handler();

const Port_ConfigType  UserConfig_PortA1 = {
  .Mux = PORT_MUX_ALT2, 
  .pull = PULL_UP,
};

const Port_ConfigType  UserConfig_PortA2 = {
  .Mux = PORT_MUX_ALT2, 
  .pull = PULL_UP,
};

const Port_ConfigType  UserConfig_PortC3 = {
  .Mux = PORT_MUX_GPIO, 
  .pull = PULL_UP,
  .IRQ = PORT_IRQ_EDGE_FALLING,
};

const Port_ConfigType  UserConfig_PortD5 = {
  .Mux = PORT_MUX_GPIO, 
};

const Port_ConfigType  UserConfig_PortE29 = {
  .Mux = PORT_MUX_GPIO, 
};

PIT_ConfigType UserConfig_PIT = {
  .Channel      = PIT_CHANNEL_0,
  .FreezeMode   = PIT_MODE_RUN,
  .IntEnable    = PIT_INTERRUPT_ENABLE,
  .PeriodTime   = 5000u,  // 1000ms
  .Callback     = &myTimer_Handler,
};

UART_ConfigType Userconfig_UART = {
  .Mode         = UART_MODE_8BIT,
  .Parity       = UART_PARITY_DISABLE,
  .Stopbit      = UART_STOPBIT_ONE,
  .OSR          = 4u,
  .SBR          = 52u,
  .RIEINT       = UART_RIEINT_ENABLE,
  .Callback     = &myUART_Handler,
};

/*static boolean status = false;*/

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/



static void myTimer_Handler(uint8_t Channel)
{
//  if (Channel == 0)
//  {
//    // Toggle Green LED
//    Toggle_GREEN_LED();
//    
//    // Trigger for ADC conversion
//    ADC_Trigger_Conversion(ADC_CHANNEL_A, 26);
//  }
//  if (Channel == 1)
//  {
//    
//  }
}



volatile uint8_t a[10000];

volatile uint32_t index = 0;

static void myUART_Handler()
{
  // Read data
  uint8_t data = UART0->D;
  if (index > 1000u)
  {
    return;
  }
  a[index] = data;
  index++;
  }



void PORTC_PORTD_IRQHandler(void)
{
  // Check if interupt from Port C.3 
  if ((PORTC->ISFR & (1 << 3)) != 0)
  {
    // Clear ISF flag
    PORT_EXTI_ClearFlag (PORTC, 3);
  
    // Delay for debouncing
    uint32_t count = 4000;
    while(--count);

    // Check button state
    if (READ_BTN1() == 0) 
    {
      uint32_t i;
      for (i=0; i<1000; i++)
      {
        UART_SendChar(a[i]);
      }
    }
  }
}



void RED_LED_Config(void)
{
  // Enable clock for PORTE, GPIOE
  SIM->SCGC5 |= SIM_SCGC5_PORTE(1);  
  
  // Config Port E
  PORT_Init(PORTE, 29, &UserConfig_PortE29);
  
  // PinE.29 = Output
  GPIO_Init(GPIOE, 29, GPIO_IO_OUTPUT);
}



void BLUE_LED_Config(void)
{
  // Enable clock for PORTD, GPIOD
  SIM->SCGC5 |= SIM_SCGC5_PORTD(1);  
  
  // Config Port D
  PORT_Init(PORTD, 5, &UserConfig_PortD5);
  
  // PinD.5 = Output
  GPIO_Init(GPIOD, 5, GPIO_IO_OUTPUT);
}



void BTN1_Config(void)
{
  // Enable Clock for Port C
  SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
  
  // Config Port C
  PORT_Init(PORTC, 3, &UserConfig_PortC3);
  
  // PinC.3 = Input
  GPIO_Init(GPIOC, 3, GPIO_IO_INPUT);
  
  // Setup interupt for Port C & Port D, priority lever = 1
  PORT_EXTI_Config(PORTC_PORTD_IRQn, 1);
}



uint8_t READ_BTN1()
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}



void PIT_Config_5s()
{
  PIT_Init(&UserConfig_PIT);
  NVIC_EnableIRQ(PIT_IRQn);
  NVIC_SetPriority(PIT_IRQn, 1);
}



void UART_User_Config()
{
  // Clock for Baudrate - MCGIRCLK 2Mhz
  MCG->C1 |= MCG_C1_IRCLKEN(1u);
  MCG->C2 |= MCG_C2_IRCS(1u);
  SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(3u);
  
  // CLOCK - Peripheral Clock (PORTA/ UART0)
  SIM->SCGC5 |= SIM_SCGC5_PORTA(1u);
  SIM->SCGC4 |= SIM_SCGC4_UART0(1u);

  // PORT  - PORTA1 (UART0_Rx) - PORTA2 (UART0_Tx) - Alt 2 - Pullup enable
  PORT_Init(PORTA, 1, &UserConfig_PortA1);
  PORT_Init(PORTA, 2, &UserConfig_PortA2);
  
  // Config for UART
  UART_Init(&Userconfig_UART);
  
  // Enable Receive
  UART0->C2 |= UART0_C2_RE(1u);
  
  // NVIC enable interupt
  NVIC_EnableIRQ(UART0_IRQn);
  
  // NVIC Set Priority
  NVIC_SetPriority(UART0_IRQn, 0);
}



