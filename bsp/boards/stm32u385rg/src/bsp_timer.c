#include "bsp_timer.h"
#include "bsp_clock.h"
/* Compteur global */
static volatile uint32_t bsp_tick;

/* Handler SysTick */
void SysTick_Handler(void);
