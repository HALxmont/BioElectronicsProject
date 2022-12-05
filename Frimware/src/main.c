#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stm32f1xx_hal.h"
#include "HardwareInit.h"
#include "main.h"
#include "UI.h"
#include "defs.h"
#include "stm32f1xx.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef dma1adc1;
extern ADC_HandleTypeDef hadc1;
extern uint16_t  adcValue[ADC_BUFF_SIZE];

int main(void)
{

  SystemClock_Config();
  HardwareInit();

ADC_Enable(&hadc1);
HAL_ADC_Start_DMA(&hadc1, &adcValue, ADC_BUFF_SIZE);




  while (1){
   // myprintf("%d,  %d,  %d, %d,\n\r", adcValue[0], adcValue[1],adcValue[2] ,adcValue[3]);  //PRINT RAW VALUES
    //HAL_Delay(1000);
  }
}















