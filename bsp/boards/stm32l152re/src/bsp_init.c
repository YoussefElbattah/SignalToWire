#include "bsp_clock.h"
#include "bsp_gpio.h"
#include "bsp_timer.h"

int bsp_init(void)
{
    bsp_clock_init();
    bsp_gpio_init();
    bsp_timer_init();
    return 0;
}