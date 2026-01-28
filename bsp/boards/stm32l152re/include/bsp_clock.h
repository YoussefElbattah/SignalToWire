#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

#include <stdint.h>

#define BSP_HSI_HZ 16000000U

int bsp_clock_init(void);

uint32_t bsp_clock_get_sysclk_hz(void);
uint32_t bsp_clock_get_ahb_hz(void);
uint32_t bsp_clock_get_apb1_hz(void);
uint32_t bsp_clock_get_apb2_hz(void);
#endif /* BSP_CLOCK_H */