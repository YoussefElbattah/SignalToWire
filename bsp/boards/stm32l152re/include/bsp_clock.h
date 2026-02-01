#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

#include <stdint.h>

#define RCC_BASE 0x40023800UL
#define BSP_HSI_HZ 16000000U

int bsp_clock_init(void);

uint32_t bsp_clock_get_sysclk_hz(void);
uint32_t bsp_clock_get_ahb_hz(void);
uint32_t bsp_clock_get_apb1_hz(void);
uint32_t bsp_clock_get_apb2_hz(void);
void bsp_clock_enable_ahb(uint32_t mask);
void bsp_clock_enable_apb1(uint32_t mask);
void bsp_clock_enable_apb2(uint32_t mask);
#endif /* BSP_CLOCK_H */