#include "bsp_clock.h"

#include <stdint.h>

#define RCC_BASE 0x40023800UL

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} rcc_reg_t;

static rcc_reg_t * const RCC = (rcc_reg_t *)RCC_BASE;

int bsp_clock_init(void){
    RCC->CR |= (1 << 0); // Enable HSI
    while (!(RCC->CR & (1 << 1))); // Wait until HSI is ready
    /*  Select HSI as system clock
    *   REG = (REG & ~MASK) | VALUE;
    */ 
    RCC->CFGR = (RCC->CFGR & ~(3 << 0)) | (1 << 0);


    while((RCC->CFGR & (3 << 2)) != (1 << 2));

    return 0;
}

uint32_t bsp_clock_get_sysclk_hz(void){
    if(((RCC->CFGR >> 2) & 0x3) == 1)
        return BSP_HSI_HZ;
    // Add more clock source checks as needed
    return BSP_HSI_HZ; // Default to HSI
}

uint32_t bsp_clock_get_ahb_hz(void){
    uint32_t sysclk = bsp_clock_get_sysclk_hz();
    uint32_t hpre = (RCC->CFGR >> 4) & 0xF;

    // AHB prescaler table to convert hpre to division factor
    static const uint16_t ahb_prescaler_table[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 64,
        128, 256, 512};

    return sysclk / ahb_prescaler_table[hpre];
}


uint32_t bsp_clock_get_apb1_hz(void){
    uint32_t ahbfreq = bsp_clock_get_ahb_hz();
    uint32_t ppre1 = (RCC->CFGR >> 8) & 0x7;

    // APB1 prescaler table to convert ppre1 to division factor
    static const uint16_t apb1_prescaler_table[] = {
        1, 1, 1, 1, 2, 4, 8, 16 
    };

    return ahbfreq / apb1_prescaler_table[ppre1];
}

uint32_t bsp_clock_get_apb2_hz(void){
    uint32_t ahbfreq = bsp_clock_get_ahb_hz();
    uint32_t ppre2 = (RCC->CFGR >> 11) & 0x7;

    // APB2 prescaler table to convert ppre2 to division factor
    static const uint8_t apb2_prescaler_table[] = {
        1, 1, 1, 1, 2, 4, 8, 16 
    };

    return ahbfreq / apb2_prescaler_table[ppre2];
}