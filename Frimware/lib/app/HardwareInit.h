
/*! 
 *  \brief     Pretty nice class.
 *  \details   This class is used to demonstrate a number of section commands.
 *  \author    John Doe
 *  \version   4.1a
 *  \date      1990-2011
 *  \pre       First initialize the system.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */

#ifndef HARDWAREINIT_H_
#define HARDWAREINIT_H_
#include"stm32f1xx.h"

typedef enum {WAITING = 0, PENDING = !WAITING} ExtIntStatus;

/** \brief Time base of the Julian Calendar
 * 
 */
#define JULIAN_DATE_BASE	2440588

/** \brief RTC time structure 
 * 
 */
// typedef struct {

// 	uint16_t year;
// 	uint8_t  month;
// 	uint8_t  day;
// 	uint8_t  hour;
// 	uint8_t  minute;
// 	uint8_t  second;

// } RTC_DateTimeTypeDef;


/**
 * \brief   The function bar. 
 * \details This function does something which is doing nothing. So this text
 * \note    This text shall only show you, how such a \"note\" section
 * \param[in]     a    Description of parameter a.
 * \param[out]    b    Description of the parameter b.
 * \param[in,out] c    Description of the parameter c.
 * \return        The error return code of the function.
 * \retval        ERR_SUCCESS    The function is successfully executed
 * \retval        ERR_FAILURE    An error occurred
 */
void HardwareInit();
void SystemClock_Config(void);
void myprintf(const char *fmt, ...);
void Uart_init(void);
void Gpio_Init(void);
void Uart_init2(void);
void Gpio_Init2(void);
void TIM_Init(void);
void DAQ_Init(void);
void SPI1_Init(void);
void DigitalInput_Init(void);
void ADC1_Init(void);
void ADC3_Init(void);
void SPI1_SDInit(void);
void RTC_Init(void);

#endif
