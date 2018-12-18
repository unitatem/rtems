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

// #include <rtems.h>
#include <rtems/test.h>
#include <bsp/io.h>

#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* forward declarations to avoid warnings */
rtems_task Init(rtems_task_argument argument);
rtems_task blink_task(rtems_task_argument argument);


const char rtems_test_name[] = "BLINK";


rtems_task Init(rtems_task_argument ignored) {
  rtems_test_begin();

  printf("Spawning task\n" );

  rtems_name name = rtems_build_name( 'B', 'L', 'N', 'K' );
  rtems_id tid;
  rtems_status_code status = rtems_task_create(
    name, 1, RTEMS_MINIMUM_STACK_SIZE,RTEMS_NO_PREEMPT, RTEMS_FLOATING_POINT, &tid);
  if (status != RTEMS_SUCCESSFUL) {
      printf("rtems_task_create failed with status of %d\n", status);
      exit(1);
  }

  status = rtems_task_start(tid, blink_task, 0);
  if (status != RTEMS_SUCCESSFUL) {
      printf( "rtems_task_start failed with status of %d\n", status);
      exit(1);
  }

  rtems_test_end();

  // delete init task after starting tasks
  status = rtems_task_delete(RTEMS_SELF);
  exit(0);
}

rtems_task blink_task(rtems_task_argument argument)
{
  stm32f4_gpio_config config;
  config.fields.pin_first = STM32F4_GPIO_PIN(3, 12);
  config.fields.pin_last = STM32F4_GPIO_PIN(3, 13);
  config.fields.mode = STM32F4_GPIO_MODE_OUTPUT;
  config.fields.otype = STM32F4_GPIO_OTYPE_PUSH_PULL;
  config.fields.ospeed = STM32F4_GPIO_OSPEED_2_MHZ;
  config.fields.pupd = STM32F4_GPIO_NO_PULL;
  config.fields.output = 1;
  config.fields.af = 0;
  stm32f4_gpio_set_config(&config);
  
  while (true) {
    stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3,12), 1);
    stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3,13), 0);
    printf("PING\n");
    rtems_task_wake_after(1 * rtems_clock_get_ticks_per_second());

    stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3,12), 0);
    stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3,13), 1);
    printf("\tPONG\n");
    rtems_task_wake_after(1 * rtems_clock_get_ticks_per_second());
  }
}

/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            2
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
