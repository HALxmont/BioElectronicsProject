

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"

#define ADC_BUFF_SIZE 4
#define MA_SIZE    256

/**
 * \brief   Debug mode indicator 0 - Release, !0 - Debug.
 */
#define DEBUG 0

/**
 * \brief   ADC moving average mode indicator. 0 == FALSE. 1 == TRUE
 */
#define MA 0


/**
 * \brief   Defines Uart timeout used in Transmission
 */
#define UartTimeout 400

/**
 * \brief   User interface: Bottons and Leds
 * \warning Led2 connected to the SDIO PIN, SW2 and SW3 labels related to the silckscreen description
 */

#define Led1_Port GPIOB
#define Led1_Pin GPIO_PIN_9
#define Led1_ON() HAL_GPIO_WritePin(Led1_Port, Led1_Pin, SET);
#define Led1_OFF() HAL_GPIO_WritePin(Led1_Port, Led1_Pin, RESET);
#define Led1_Toggle() HAL_GPIO_TogglePin(Led1_Port, Led1_Pin);
#define Led2_Port GPIOA
#define Led2_Pin GPIO_PIN_13
#define Led2_ON() HAL_GPIO_WritePin(Led2_Port, Led2_Pin, SET);
#define Led2_OFF() HAL_GPIO_WritePin(Led2_Port, Led2_Pin, RESET);
#define Led2_Toggle() HAL_GPIO_TogglePin(Led2_Port, Led2_Pin);
#define SW2_Port GPIOB
#define SW2_Pin GPIO_PIN_8
#define SW2() HAL_GPIO_ReadPin(SW2_Port, SW2_Pin);
#define SW3_Port GPIOB
#define SW3_Pin GPIO_PIN_15
#define SW3() HAL_GPIO_ReadPin(SW3_Port, SW3_Pin);



/**
 * \brief   Digital inputs configuration
 *          Should be asociated with External interrupts
 * \warning
 */
#define DIN1_Port GPIOC
#define DIN1_Pin GPIO_PIN_4
#define DIN1_ON() HAL_GPIO_WritePin(DIN1_Port, DIN1_Pin, SET);
#define DIN1_OFF() HAL_GPIO_WritePin(DIN1_Port, DIN1_Pin, RESET);
#define DIN1_Toggle() HAL_GPIO_TogglePin(DIN1_Port, DIN1_Pin);
#define DIN1() HAL_GPIO_ReadPin(DIN1_Port, DIN1_Pin);

#define DIN2_Port GPIOC
#define DIN2_Pin GPIO_PIN_5
#define DIN2_ON() HAL_GPIO_WritePin(DIN2_Port, DIN2_Pin, SET);
#define DIN2_OFF() HAL_GPIO_WritePin(DIN2_Port, DIN2_Pin, RESET);
#define DIN2_Toggle() HAL_GPIO_TogglePin(DIN2_Port, DIN2_Pin);
#define DIN2() HAL_GPIO_ReadPin(DIN2_Port, DIN2_Pin);

#define DIN3_Port GPIOB
#define DIN3_Pin GPIO_PIN_12
#define DIN3_ON() HAL_GPIO_WritePin(DIN3_Port, DIN3_Pin, SET);
#define DIN3_OFF() HAL_GPIO_WritePin(DIN3_Port, DIN3_Pin, RESET);
#define DIN3_Toggle() HAL_GPIO_TogglePin(DIN3_Port, DIN3_Pin);
#define DIN3() HAL_GPIO_ReadPin(DIN3_Port, DIN3_Pin);




/**
 * \brief   Local UART
 * \warning
 */
#define TX_Local_Port   GPIOA
#define TX_Local_Pin    GPIO_PIN_9
#define RX_Local_Port   GPIOA
#define RX_Local_Pin    GPIO_PIN_10

/**
 * \brief   Communication Uart
 * \warning
 */
#define TX_Port   GPIOA
#define TX_Pin    GPIO_PIN_2
#define RX_Port   GPIOA
#define RX_Pin    GPIO_PIN_3



/**
 * \brief   Analog ports 
 *          Analog_Voltage0 = AD-ch0
 *          Analog_Voltage1 = AD-ch1
 *          Analog_Voltage2 = AD-ch2
 *          Analog_Voltage3 = AD-ch3
                      
 * \warning
 */

 
#define Analog_Voltage_Port           GPIOA
#define Analog_Voltage0               GPIO_PIN_0
#define Analog_Voltage1               GPIO_PIN_1
#define Analog_Voltage2               GPIO_PIN_2
#define Analog_Voltage3               GPIO_PIN_3

#endif
