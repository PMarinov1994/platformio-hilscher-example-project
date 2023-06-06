/**************************************************************************//**
 * @file    main.c
 * @brief   Main program body
 * $Revision: 4507 $
 * $Date: 2018-11-20 13:25:13 +0100 (Di, 20 Nov 2018) $
 * \copyright Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
 * \note Exclusion of Liability for this demo software:
 * The following software is intended for and must only be used for reference and in an
 * evaluation laboratory environment. It is provided without charge and is subject to
 * alterations. There is no warranty for the software, to the extent permitted by
 * applicable law. Except when otherwise stated in writing the copyright holders and/or
 * other parties provide the software "as is" without warranty of any kind, either
 * expressed or implied.
 * Please refer to the Agreement in README_DISCLAIMER.txt, provided together with this file!
 * By installing or otherwise using the software, you accept the terms of this Agreement.
 * If you do not agree to the terms of this Agreement, then do not install or use the
 * Software!
 ******************************************************************************/

#include "blinky_demo.h"

#include "gpio.h"
#include "systime.h"
#include "rdy_run.h"

unsigned int LEDs[] =
{
  GPIO_LED_0,
  GPIO_LED_1,
  GPIO_LED_2,
  GPIO_LED_3,
};

/*
 * Read the README.txt file for more information.
 */
int blinky_demo(void)
{
  systime_init();
  Gpio_Init();

  for(int i = 0; i < ARRAY_SIZE(LEDs); i++)
    Gpio_SetupMode_Output_To_Line(LEDs[i]);

  while(1)
  {
    // Turn all LEDs on
    for(int i = 0; i < ARRAY_SIZE(LEDs); i++)
    {
      // Flash the sys led.
      if(i % 2 == 0)
        rdy_run_setLEDs(RDYRUN_YELLOW);
      else
        rdy_run_setLEDs(RDYRUN_GREEN);

      Gpio_SetOutput(LEDs[i], LED_ON);
      systime_delay_ms(100);
    }

    // Turn all LEDs off
    for(int i = 0; i < ARRAY_SIZE(LEDs); i++)
    {
      // Flash the sys led.
      if(i % 2 == 0)
        rdy_run_setLEDs(RDYRUN_YELLOW);
      else
        rdy_run_setLEDs(RDYRUN_GREEN);

      Gpio_SetOutput(LEDs[i], LED_OFF);
      systime_delay_ms(100);
    }
  }

  return 0;
}
