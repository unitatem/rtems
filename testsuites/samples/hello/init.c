/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/test.h>
#include <bsp/io.h>

#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>

/* forward declarations to avoid warnings */
rtems_task Init(rtems_task_argument argument);

const char rtems_test_name[] = "HELLO WORLD";

rtems_task Init(
  rtems_task_argument ignored
)
{
  rtems_test_begin();

  printf( "Hello World\n" );

  stm32f4_gpio_config config;
  config.fields.pin_first = STM32F4_GPIO_PIN(3, 12);
  config.fields.pin_last = STM32F4_GPIO_PIN(3, 12);
  config.fields.mode = STM32F4_GPIO_MODE_OUTPUT;
  config.fields.otype = STM32F4_GPIO_OTYPE_PUSH_PULL;
  config.fields.ospeed = STM32F4_GPIO_OSPEED_2_MHZ;
  config.fields.pupd = STM32F4_GPIO_NO_PULL;
  config.fields.output = 1;
  config.fields.af = 0;
  stm32f4_gpio_set_config(&config);

  stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3,12), 1);
  
  rtems_test_end();
  exit( 0 );
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            1
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
