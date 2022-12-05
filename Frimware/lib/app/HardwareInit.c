#include "HardwareInit.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rtc.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "UI.h"
#include "defs.h"

UART_HandleTypeDef huart1;
DMA_HandleTypeDef dma1;
DMA_HandleTypeDef dma1adc1;
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htmr;

extern char UI_Buffer[UI_Buff_Size];
extern uint16_t adcValue[ADC_BUFF_SIZE];

void HardwareInit()
{
  HAL_Init();
  Gpio_Init();
  Uart_init();
 // TIM_Init();
  ADC1_Init();
}

void Gpio_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_USART1_CLK_ENABLE(); // UI UART

  GPIO_InitTypeDef GPIO_InitStruct;


//INPUTS
  GPIO_InitStruct.Pin = SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SW2_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SW3_Port, &GPIO_InitStruct);



//ADC ANALOG INPUTS PINS

  /*------------------ADC  CH0  Pins Configuration begins -----------------------------*/
  GPIO_InitStruct.Pin = Analog_Voltage0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Analog_Voltage_Port, &GPIO_InitStruct);

  /*------------------ADC  CH1  Pins Configuration begins -----------------------------*/
  GPIO_InitStruct.Pin = Analog_Voltage1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Analog_Voltage_Port, &GPIO_InitStruct);

  /*------------------ADC  CH2  Pins Configuration begins -----------------------------*/
  GPIO_InitStruct.Pin = Analog_Voltage2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Analog_Voltage_Port, &GPIO_InitStruct);

  /*------------------ADC  CH3  Pins Configuration begins -----------------------------*/
  GPIO_InitStruct.Pin = Analog_Voltage3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Analog_Voltage_Port, &GPIO_InitStruct);


  /*------------------UART 1 Pins Configuration begins -----------------------------*/

  GPIO_InitStruct.Pin = TX_Local_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TX_Local_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RX_Local_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RX_Port, &GPIO_InitStruct);


//INTERRUPTS PRIORITY
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

 }

void Uart_init(void)
{

  __HAL_RCC_DMA1_CLK_ENABLE();
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  
  if (HAL_UART_Init(&huart1) != HAL_OK)
    asm("bkpt 255");

  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);


  dma1.Instance = DMA1_Channel5;
  dma1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  dma1.Init.PeriphInc = DMA_PINC_DISABLE;
  dma1.Init.MemInc = DMA_MINC_ENABLE;
  dma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  dma1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  dma1.Init.Mode = DMA_NORMAL;
  dma1.Init.Priority = DMA_PRIORITY_HIGH;
  HAL_DMA_Init(&dma1);
  __HAL_LINKDMA(&huart1, hdmarx, dma1);
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart1, UI_Buffer, UI_Buff_Size); //link UI buffer to DMA1


  /*------------------UART  Configuration ends -------------------------------*/
}



void ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig = {0};
 // __HAL_RCC_ADC1_CLK_ENABLE();

  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  //hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  
  hadc1.Init.NbrOfDiscConversion = ADC_BUFF_SIZE;
  hadc1.Init.NbrOfConversion = ADC_BUFF_SIZE;

  /*  Current 1 */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  /* Current channel 2*/
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  /* Voltage channel 1*/
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  /* Voltage Channel 2*/
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  dma1adc1.Instance = DMA1_Channel1;
  dma1adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  dma1adc1.Init.PeriphInc = DMA_PINC_DISABLE;
  dma1adc1.Init.MemInc = DMA_MINC_ENABLE;
  dma1adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  dma1adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  dma1adc1.Init.Mode = DMA_CIRCULAR;
  dma1adc1.Init.Priority = DMA_PRIORITY_HIGH;
  HAL_DMA_Init(&dma1adc1);
  __HAL_LINKDMA(&hadc1, DMA_Handle, dma1adc1);
  HAL_ADC_Init(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc1);
  __HAL_DMA_ENABLE_IT(&dma1adc1, DMA_IT_TC);

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

  
}




void TIM_Init(void)
{
  __TIM3_CLK_ENABLE();
  TIM_MasterConfigTypeDef mhtmr;


  htmr.Instance = TIM3;
  htmr.Init.Prescaler = 3199;
  htmr.Init.CounterMode = TIM_COUNTERMODE_UP;
  htmr.Init.Period = 10; // auto reload register
  htmr.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htmr.Init.RepetitionCounter = 0;
  htmr.Instance->CCR1 = 1000;
  HAL_TIM_Base_Init(&htmr);
  TIM3->CCER |= 0x22;
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  __HAL_TIM_ENABLE_IT(&htmr, TIM_IT_UPDATE);
  __HAL_TIM_ENABLE_IT(&htmr, TIM_IT_CC1);

  // mhtmr.MasterOutputTrigger = TIM_TRGO_UPDATE;
  // mhtmr.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  // HAL_TIMEx_MasterConfigSynchronization(&htmr, &mhtmr);
 // HAL_TIM_Base_Start(&htmr);
}




void myprintf(const char *fmt, ...)
{
  static char buffer[256];
  __va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  int len = strlen(buffer);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len, -1);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef rccPeriphCLKInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
      in the RCC_OscInitTypeDef structure.*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSI; // HSE and LSI oscilator
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON; // rtc clock source enable
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  __HAL_RCC_ADC1_CLK_ENABLE();

  rccPeriphCLKInit.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_RTC;
  rccPeriphCLKInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;

  rccPeriphCLKInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI; // RTC clock source

  HAL_RCCEx_PeriphCLKConfig(&rccPeriphCLKInit);
}
