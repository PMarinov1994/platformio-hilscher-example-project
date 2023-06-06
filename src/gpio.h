/*
 * gpio.h
 *
 *  Created on: Jun 23, 2021
 *      Author: PMarinova
 */

#ifndef __GPIO_H_
#define __GPIO_H_

#include "asic_types.h"

#if ASIC_TYP == ASIC_TYP_NETX90_APP || ASIC_TYP == ASIC_TYP_NETX90 || ASIC_TYP == ASIC_TYP_NETX10 || ASIC_TYP == ASIC_TYP_NETX56

/* For netx10/56/90 the MMIO to GPIO mapping is made inside the mmio_config.c file for the chip type.     */
/*      LED No      |  GPIO No                                                                         */
#define GPIO_LED_0     0
#define GPIO_LED_1     1
#define GPIO_LED_2     2
#define GPIO_LED_3     3

#elif ASIC_TYP == ASIC_TYP_NETX500

/*      LED No      |  GPIO No                                                                         */
#define GPIO_LED_0      8
#define GPIO_LED_1      9
#define GPIO_LED_2     10
#define GPIO_LED_3     11

#endif

#define LED_ON 1
#define LED_OFF 0

void Gpio_Init();
void Gpio_SetupMode_Output_To_Line( unsigned long ulGpioNum );
void Gpio_SetOutput( unsigned short ulGpioNum, int fEnable );

#endif /* __GPIO_H_ */
