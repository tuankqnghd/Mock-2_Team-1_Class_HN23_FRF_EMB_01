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

#define VECTOR_TABLE_FLASH_ADDRESS  ((uint32*)0x00000000u)
#define VECTOR_TABLE_RAM_ADDRESS    ((uint32*)0x20004000u)
#define VECTOR_TABLE_SIZE           (256u)

/*********************************************************************
* Variable
*********************************************************************/

static void myTimer_Handler(uint8 Channel);

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

const Port_ConfigType  UserConfig_PortC12 = {
  .Mux = PORT_MUX_GPIO, 
  .pull = PULL_UP,
  .IRQ = PORT_IRQ_EDGE_FALLING,
};


//const Port_ConfigType  UserConfig_PortD5 = {
//  .Mux = PORT_MUX_GPIO, 
//};
//
//const Port_ConfigType  UserConfig_PortE29 = {
//  .Mux = PORT_MUX_GPIO, 
//};

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



static void myTimer_Handler(uint8 Channel)
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

volatile uint32 Address = 0;

volatile uint32 Data = 0; 

volatile uint32 ByteCount = 0; 

volatile uint32 DataByteCount = 0;

volatile uint8 FlagCheck[] = {0, 0, 0, 0, 0, 0, 0};

//volatile uint32 data[256];
//
//volatile uint32 address[256];

#define START_SREC                  (0u)

#define START_STYPE                 (1u)

#define START_BYTECOUNT             (2u)

#define ADDRESS_BYTECOUNT           (3u)

#define START_ADDRESS               (4u)

#define DATA_BYTECOUNT              (5u)

#define START_DATA                  (6u)

uint8 DataShift[] = {4, 0, 12, 8, 20, 16, 28, 24};


void myUART_Handler()
{
  // Read data
  uint8 ReceiveData = UART0->D;
  
  if (ReceiveData == 'S')
  {
    FlagCheck[START_STYPE] = 1;
  }
  else if (FlagCheck[START_STYPE] == 1)
  {
    if (ReceiveData == '0')         // S0
    {
      FlagCheck[START_SREC] = 1;
    }
    else if ((ReceiveData == '7') || (ReceiveData == '8') || (ReceiveData == '9'))    // S7/S8/S9
    {
      FlagCheck[START_SREC] = 0;
    }
    else if (ReceiveData == '1')   // S1
    {
      FlagCheck[START_BYTECOUNT] = 1;
      FlagCheck[ADDRESS_BYTECOUNT] = 2;
    }
    else if (ReceiveData == '2')   // S2
    {
      FlagCheck[START_BYTECOUNT] = 1;
      FlagCheck[ADDRESS_BYTECOUNT] = 3;
    }
    else if (ReceiveData == '3')   // S3
    {
      FlagCheck[START_BYTECOUNT] = 1;
      FlagCheck[ADDRESS_BYTECOUNT] = 4;
    }
    // Return START_STYPE
    FlagCheck[START_STYPE] = 0;
    }
    else if (FlagCheck[START_BYTECOUNT] == 1)
    {
      // Bytecount = 0x13;
      ByteCount = ChartoHex(ReceiveData) << 4;
      FlagCheck[START_BYTECOUNT] = 2;
    }
    else if (FlagCheck[START_BYTECOUNT] == 2)
    {
      ByteCount += ChartoHex(ReceiveData);
      FlagCheck[START_BYTECOUNT] = 0;
      FlagCheck[START_ADDRESS] = 1;
      
      // Return Address = 0
      Address = 0;
      
      DataByteCount = ByteCount - 1u - FlagCheck[ADDRESS_BYTECOUNT];
    }
    else if (FlagCheck[START_ADDRESS] != 0)
    {
      Address += ChartoHex(ReceiveData) << ((FlagCheck[ADDRESS_BYTECOUNT] << 3) - (FlagCheck[START_ADDRESS] << 2));
        
      FlagCheck[START_ADDRESS]++;
      if (FlagCheck[START_ADDRESS] == (FlagCheck[ADDRESS_BYTECOUNT] << 1) + 1)
      {
        FlagCheck[START_ADDRESS] = 0;
        FlagCheck[START_DATA] = 1;
      }
    }
    else if (FlagCheck[START_DATA] != 0)
    {
      // character -> all bytes data
      Data += ChartoHex(ReceiveData) << DataShift[(FlagCheck[START_DATA] - 1)];
      FlagCheck[START_DATA] = FlagCheck[START_DATA] + 1;
      FlagCheck[DATA_BYTECOUNT] = FlagCheck[DATA_BYTECOUNT] + 1;
      if (FlagCheck[DATA_BYTECOUNT] >= (DataByteCount*2))
      {
        // enque
        enqueue(Address + (FlagCheck[DATA_BYTECOUNT]-8)/2, Data);
        
        // Return flag
        FlagCheck[DATA_BYTECOUNT] = 0;
        FlagCheck[START_DATA] = 0;
        
        // Return Data
        Data = 0;
      }
      if (FlagCheck[START_DATA] > 8)
      {
        // enque
        enqueue(Address + (FlagCheck[DATA_BYTECOUNT]-8)/2, Data);
        
        // Return START_DATA flag to read more data
        FlagCheck[START_DATA] = 1;
        
        // Return Data
        Data = 0;
      }
    }
}



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
    }
  }
  
  // Check if interupt from Port C.12 
  if ((PORTC->ISFR & (1 << 12)) != 0)
  {
    // Clear ISF flag
    PORT_EXTI_ClearFlag (PORTC, 12);
  
    // Delay for debouncing
    uint32 count = 4000;
    while(--count);
    uint8 i = 0;
    
    // Check button state
    if (READ_BTN2() == 0) 
    {
      for (i = 0; i < 11; i++)
      {
        Flash_EraseSector(0x00001400u + i*0x400);
      }
    }
  }
}



void Copy_Vector_Table_SetVTOR(void)
{
  uint32 i = 0;
  // Copy vector table from flash to vectorTable[256] (RAM)
  for (i = 0; i < VECTOR_TABLE_SIZE; i++) 
  {
    VECTOR_TABLE_RAM_ADDRESS[i] = VECTOR_TABLE_FLASH_ADDRESS[i];
  }
  
  // Set new VTOR
  SCB->VTOR = (uint32)VECTOR_TABLE_RAM_ADDRESS;
}



void ReturnVTOR(void)
{
  // return VTOR
  SCB->VTOR = (uint32)VECTOR_TABLE_FLASH_ADDRESS;
}



//void RED_LED_Config(void)
//{
//  // Enable clock for PORTE, GPIOE
//  SIM->SCGC5 |= SIM_SCGC5_PORTE(1);  
//  
//  // Config Port E
//  PORT_Init(PORTE, 29, &UserConfig_PortE29);
//  
//  // PinE.29 = Output
//  GPIO_Init(GPIOE, 29, GPIO_IO_OUTPUT);
//}
//
//
//
//void BLUE_LED_Config(void)
//{
//  // Enable clock for PORTD, GPIOD
//  SIM->SCGC5 |= SIM_SCGC5_PORTD(1);  
//  
//  // Config Port D
//  PORT_Init(PORTD, 5, &UserConfig_PortD5);
//  
//  // PinD.5 = Output
//  GPIO_Init(GPIOD, 5, GPIO_IO_OUTPUT);
//}



void BTN_Config(void)
{
  // Enable Clock for Port C
  SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
  
  // Config Port C
  PORT_Init(PORTC, 3, &UserConfig_PortC3);
  PORT_Init(PORTC, 12, &UserConfig_PortC3);
  
  // PinC.3 = Input
  GPIO_Init(GPIOC, 3, GPIO_IO_INPUT);
  GPIO_Init(GPIOC, 12, GPIO_IO_INPUT);
  
  // Setup interupt for Port C & Port D, priority lever = 1
  PORT_EXTI_Config(PORTC_PORTD_IRQn, 1);
}



uint8 READ_BTN1()
{
  return ((FGPIOC->PDIR & (1 << 3)) >> 3);
}



uint8 READ_BTN2()
{
  return ((FGPIOC->PDIR & (1 << 12)) >> 12);
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



uint8 ChartoHex(char c)
{
  if ((48<=c)&&(c<=57))
  {
    return (c-48);
  }
  else if ((65<=c)&&(c<=70))
  {
    return (c-55);
  }
  else 
  {
    return 255u;
  }
}



void FirmwaretoFlash(void)
{
    while (isQueueEmpty());
    FlashData a = dequeue();
    while (!Flash_IsReady());
    Flash_WriteWord(a.address, a.data);
}







