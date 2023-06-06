/*
 * gpio.c
 *
 *  Created on: Jun 23, 2021
 *      Author: PMarinova
 */

#include "gpio.h"

#include "netx_regdef.h"

#if ASIC_TYP==ASIC_TYP_NETX90_APP || ASIC_TYP==ASIC_TYP_NETX90

#include "netx90/mmio_config.h"
#define GPIO_MODE_OUTPUT_SET_TO_GPIO_LINE 0x6

#elif ASIC_TYP==ASIC_TYP_NETX56

#include "netx56/mmio_config.h"
#define GPIO_MODE_OUTPUT_SET_TO_GPIO_LINE 0x6
#define NX56_GPIO_INVERT_FALSE 0
#define NX56_GPIO_INVERT_TRUE 1

#elif ASIC_TYP == ASIC_TYP_NETX500

#define NX500_GPIO_CFG_INPUT 1
#define NX500_GPIO_CFG_OUTPUT 0
#define NX500_GPIO_MODE_SET_TO_LINE 2
#define NX500_GPIO_INVERT_FALSE 0
#define NX500_GPIO_INVERT_TRUE 1

#elif ASIC_TYP == ASIC_TYP_NETX10

#include "netx10/mmio_config.h"
#define NX10_GPIO_MODE_OUTPUT_SET_TO_LINE 6
#define NX10_GPIO_INVERT_FALSE 0
#define NX10_GPIO_INVERT_TRUE 1

#endif

#define DEV_FREQUENCY 100000000L // 100 Mhz

/*
 * Creates a mapping between MMIO and GPIO for the boards that require it.
 * For netX56 and netX10 this is done in code.
 * For netX90 this is done via .hwc (hardware configuration) file.
 */
void Gpio_Init()
{
#if ASIC_TYP == ASIC_TYP_NETX56
  mmio_config_netx56();

#elif ASIC_TYP == ASIC_TYP_NETX10
  mmio_config_netx10();

#elif ASIC_TYP == ASIC_TYP_NETX90_APP
  mmio_config_netx90_app();

#endif

  return;
}

/*****************************************************************************/
/*! GPIO Setup Mode                                                          */
/*****************************************************************************/
void Gpio_SetupMode_Output_To_Line(unsigned long ulGpioNum)
{
#if ASIC_TYP == ASIC_TYP_NETX90

  return;

#elif ASIC_TYP == ASIC_TYP_NETX90_APP

  NX90_GPIO_APP_AREA_T * const ptGpioAppArea = (NX90_GPIO_APP_AREA_T * const) Addr_NX90_gpio_app;

  NX90_GPIO_APP_CFG0_T gpioCfg = { 0 };
  gpioCfg.bf.mode = GPIO_MODE_OUTPUT_SET_TO_GPIO_LINE;

  ptGpioAppArea->aulGpio_app_cfg[ulGpioNum] = gpioCfg.val;

#elif ASIC_TYP == ASIC_TYP_NETX56

  NX56_GPIO_AREA_T * const ptGpioArea = (NX56_GPIO_AREA_T * const) Addr_NX56_gpio;

  NX56_GPIO_CFG0_T gpioCfg = { 0 };
  gpioCfg.bf.mode = GPIO_MODE_OUTPUT_SET_TO_GPIO_LINE;
  gpioCfg.bf.inv = NX56_GPIO_INVERT_FALSE;

  ptGpioArea->aulGpio_cfg[ulGpioNum] = gpioCfg.val;

#elif ASIC_TYP == ASIC_TYP_NETX500

  NX500_GPIO_AREA_T * const ptGpioArea = (NX500_GPIO_AREA_T * const) Addr_NX500_gpio;

  NX500_GPIO_CFG0_T gpioCfg = { 0 };
  gpioCfg.bf.iocfg = NX500_GPIO_CFG_INPUT;
  gpioCfg.bf.mode = NX500_GPIO_MODE_SET_TO_LINE;
  gpioCfg.bf.inv = NX500_GPIO_INVERT_FALSE;

  ptGpioArea->aulGpio_cfg[ulGpioNum] = gpioCfg.val;

#elif ASIC_TYP == ASIC_TYP_NETX10

  NX10_GPIO_AREA_T * const ptGpioArea = (NX10_GPIO_AREA_T * const) Addr_NX10_gpio;

  NX10_GPIO_CFG0_T gpioCfg = { 0 };
  gpioCfg.bf.mode = NX10_GPIO_MODE_OUTPUT_SET_TO_LINE;
  gpioCfg.bf.inv = NX10_GPIO_INVERT_FALSE;

  ptGpioArea->aulGpio_cfg[ulGpioNum] = gpioCfg.val;

#endif
}

/*****************************************************************************/
/*! GPIO Set Output                                                          */
/*****************************************************************************/
void Gpio_SetOutput(unsigned short ulGpioNum, int fEnable)
{
#if ASIC_TYP == ASIC_TYP_NETX90

  return;

#elif ASIC_TYP == ASIC_TYP_NETX90_APP

  NX90_GPIO_APP_AREA_T * const ptGpioAppArea = (NX90_GPIO_APP_AREA_T * const) Addr_NX90_gpio_app;

  if(fEnable)
  ptGpioAppArea->ulGpio_app_line |= 1 << ulGpioNum;
  else
  ptGpioAppArea->ulGpio_app_line &= ~(1 << ulGpioNum);

#elif ASIC_TYP == ASIC_TYP_NETX56

  NX56_GPIO_AREA_T * const ptGpioArea = (NX56_GPIO_AREA_T * const) Addr_NX56_gpio;
  if(fEnable)
    ptGpioArea->ulGpio_line |= 1 << (ulGpioNum);
  else
    ptGpioArea->ulGpio_line &= ~(1 << (ulGpioNum));

#elif ASIC_TYP == ASIC_TYP_NETX500

  NX500_GPIO_AREA_T * const ptGpioArea = (NX500_GPIO_AREA_T * const) Addr_NX500_gpio;
  if(fEnable)
    ptGpioArea->ulGpio_line |= 1 << (ulGpioNum);
  else
    ptGpioArea->ulGpio_line &= ~(1 << (ulGpioNum));

#elif ASIC_TYP == ASIC_TYP_NETX10

  NX10_GPIO_AREA_T * const ptGpioArea = (NX10_GPIO_AREA_T * const) Addr_NX10_gpio;
  if(fEnable)
    ptGpioArea->ulGpio_line |= 1 << (ulGpioNum);
  else
    ptGpioArea->ulGpio_line &= ~(1 << (ulGpioNum));

#endif
}
