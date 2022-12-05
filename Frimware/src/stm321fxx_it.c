
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "HardwareInit.h"
#include "UI.h"
#include "defs.h"
#include "Sensors.h"
#include "fatfs.h"
#include "ff.h"

extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef dma1adc1;
extern DMA_HandleTypeDef dma1;
extern TIM_HandleTypeDef htmr;

extern uint8_t   UI_Buffer[UI_Buff_Size];


uint16_t adcValue[ADC_BUFF_SIZE];

uint32_t v0, v1, v2, v3;


void DMA1_Channel1_IRQHandler(void) // <----- The ISR Function We're Looking For!
{

  static uint16_t cnt = 0;
  static uint32_t cv0 = 0, cv1 = 0, cv2 = 0, cv3 = 0;
  static uint16_t buff1[MA_SIZE];
  static uint16_t buff2[MA_SIZE];
  static uint16_t buff3[MA_SIZE];
  static uint16_t buff4[MA_SIZE];

  if (__HAL_DMA_GET_FLAG(&dma1adc1, DMA_IT_TC) != 0x00u) {

      __HAL_DMA_CLEAR_FLAG(&dma1adc1, DMA_IT_TC);

      for (int i = 0; i < MA_SIZE; i++)
      {
        if (i > 0)
        {
          buff1[i] = buff1[i - 1];
          buff2[i] = buff2[i - 1];
          buff3[i] = buff3[i - 1];
          buff4[i] = buff4[i - 1];
        }
        cv0 += buff1[i];
        cv1 += buff2[i];
        cv2 += buff3[i];
        cv3 += buff4[i];
      }

      buff1[0] = adcValue[0];
      buff2[0] = adcValue[1];
      buff3[0] = adcValue[2];
      buff4[0] = adcValue[3];
      // myprintf("mean = %d\n\r", sum >> 4);

     //Filtered voltages 
      v0 = cv0 / MA_SIZE;
      v1 = cv1 / MA_SIZE;
      v2 = cv2 / MA_SIZE;
      v3 = cv3 / MA_SIZE;

      // Led1_Toggle();
      cnt = (cnt + 1) % MA_SIZE;

      if (cnt == 0){
        cv0 = 0;
        cv1 = 0;
        cv2 = 0;
        cv3 = 0;
      }

    if (MA) //MOVING AVERAGE ON!
      myprintf("%d,  %d,  %d, %d\n\r", v0, v1, v2, v3);  //PRINT FILTERED VALUES

    else //MOVING AVERAGE OFF!   
      myprintf("%d,  %d,  %d, %d\n\r", adcValue[0], adcValue[1],adcValue[2] ,adcValue[3]);  //PRINT RAW VALUES
    
    //HAL_Delay(1000);
  }
}




void ADC1_IRQHandler(void) // <----- The ISR Function We're Looking For!
{
  uint16_t val;
  if (ADC1->CR1 &= ADC_IT_EOC)
  {
    val = ADC1->DR;
    ADC1->SR &= ~ADC_SR_EOC;
  }
}

//######################################
//##### UART1 INTERRUPT
//######################################

void USART1_IRQHandler(void)
{
  uint8_t data_length = 0;
  char str[20];

  static uint8_t i = 0;
  if (RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE))
  {
    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
  }

  if (RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);
    HAL_UART_DMAStop(&huart1);
    data_length = UI_Buff_Size - __HAL_DMA_GET_COUNTER(&dma1);
    UI_SetParams();
    HAL_UART_Receive_DMA(&huart1, UI_Buffer, UI_Buff_Size);
    
  }
}



void SysTick_Handler(void)
{
  HAL_IncTick();
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

