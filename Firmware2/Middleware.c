/*
* @file Middleware.c
* @brief Middleware lib support user config to red, blue led, button 1, read input logic button 1 of MKL46Z4
* config core clock and delay 200ms funtion 
*/
/********************************************************************
 * Include Library
********************************************************************/
#include "MKL46Z4.h"
#include "math.h"
#include "stdio.h"
#include "Middleware.h"

/********************************************************************
 * Definition
********************************************************************/

#define V_TEMP25              (0.716)
#define M_TEMP                (0.00175)
#define V_REF                 (3.3)
#define ADC_RESOLUTION        (16)
#define ADC_READ_BUFFER_SIZE  (10)

/*********************************************************************
* Variable
*********************************************************************/

volatile uint16_t adc_data;

volatile float temp_value;

volatile float temperature[ADC_READ_BUFFER_SIZE];

volatile uint8_t data;

volatile uint8_t current_index = 0;

static void myTimer_Handler(uint8_t Channel);

static void myADC_Handler();

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
  .PeriodTime   = 1000u,  // 1000ms
  .Callback     = &myTimer_Handler,
};

ADC_ConfigType UserConfig_ADC = {
  .Channel      = ADC_CHANNEL_A,
  .Clock        = ADC_CLOCK_BUSCLK,
  .Vref         = ADC_VREF_VREFH_VREFL,
  .Mode         = ADC_MODE_SINGLE_END,
  .Resolution   = ADC_RESOLUTION_16BIT,
  .EnableINT    = ADC_INT_ENABLE,
  .Callback     = &myADC_Handler,
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
  if (Channel == 0)
  {
    // Toggle Green LED
    Toggle_GREEN_LED();
    
    // Trigger for ADC conversion
    ADC_Trigger_Conversion(ADC_CHANNEL_A, 26);
  }
  if (Channel == 1)
  {
    
  }
}



static void myADC_Handler()
{
  // Toggle Red LED
  Toggle_RED_LED();
  
  // Read data ADC
  adc_data = ADC0_Read(ADC_CHANNEL_A);
  
  temp_value = Temperature_Cal(adc_data);
  
  float temp = temp_value;
  
  temperature[current_index] = temp;
  
  current_index = (current_index + 1) % ADC_READ_BUFFER_SIZE;
}



void floatToCharArray(float number, char* buffer, int bufferSize) 
{
    sprintf(buffer, "%.2f", number);
}



static void myUART_Handler()
{
  // Read data
  data = UART0->D;
  
  uint8_t index;
  
  if (data == 0x55)
  {
    char buffer[6u];
    
    for (index = 0; index < ADC_READ_BUFFER_SIZE; index++)
    {
      floatToCharArray(temperature[index], buffer, sizeof(buffer));
      
      // char 'Space'
      buffer[5] = 0x20;

      UART_SendString(buffer, 6u);
    }
  }
}



void RED_LED_Init(void)
{
  // Enable clock for PORTE, GPIOE
  SIM->SCGC5 |= SIM_SCGC5_PORTE(1);  
  
  // Config Port E
  PORT_Init(PORTE, 29, &UserConfig_PortE29);
  
  // PinE.29 = Output
  GPIO_Init(GPIOE, 29, GPIO_IO_OUTPUT);
}



void BLUE_LED_Init(void)
{
  // Enable clock for PORTD, GPIOD
  SIM->SCGC5 |= SIM_SCGC5_PORTD(1);  
  
  // Config Port D
  PORT_Init(PORTD, 5, &UserConfig_PortD5);
  
  // PinD.5 = Output
  GPIO_Init(GPIOD, 5, GPIO_IO_OUTPUT);
}



void BTN1_Init(void)
{
  // Enable Clock for Port C
  SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
  
  // Config Port C
  PORT_Init(PORTC, 3, &UserConfig_PortC3);
  
  // PinC.3 = Input
  GPIO_Init(GPIOC, 3, GPIO_IO_INPUT);
}



void Toggle_RED_LED(void)
{
  GPIO_TogglePin(GPIOE, 29);
}



void Toggle_GREEN_LED(void)
{
  GPIO_TogglePin(GPIOD, 5);
}



uint8_t READ_BTN1()
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}



float Temperature_Cal(uint16_t ADC_value)
{
  return (25 - ((float)ADC_value / (pow(2, 16) - 1) * V_REF - V_TEMP25) / M_TEMP);
}



void PIT_Config_1s()
{
  PIT_Init(&UserConfig_PIT);
  NVIC_EnableIRQ(PIT_IRQn);
  NVIC_SetPriority(PIT_IRQn, 2);
}



void ADC_TempSensor_Config()
{
  ADC_Init(&UserConfig_ADC);
  NVIC_EnableIRQ(ADC0_IRQn);
  NVIC_SetPriority(ADC0_IRQn, 1);
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
  NVIC_SetPriority(UART0_IRQn, 3);
}



