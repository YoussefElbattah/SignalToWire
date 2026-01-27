#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include <stdint.h>

/* Initialisation base de temps */
int bsp_timer_init(void);

/* Temps */
uint32_t bsp_timer_get_ticks(void);
void bsp_timer_delay_ms(uint32_t ms);

#endif
