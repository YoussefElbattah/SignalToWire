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

}