#include "bsp_timer.h"
#include "bsp_clock.h"

#define SYST_BASE_ADDR  0xE000E010

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t RVR;
    volatile uint32_t CVR;
    volatile uint32_t CALIB;
}syst_reg_t;

/* Compteur global */
static volatile uint32_t bsp_tick;
static volatile syst_reg_t *SYST = (syst_reg_t*)SYST_BASE_ADDR;

int bsp_timer_init(void){
    uint32_t sysclk = bsp_clock_get_sysclk_hz(); // 1ms load
    uint32_t load_ms = sysclk / 1000; // by default
    
    // implement other cases as needed if - HSE, PLL, ...
    if(load_ms > 0x00FFFFFF)
        load_ms = 0x00FFFFFF;
        
    SYST->RVR = load_ms - 1;
    SYST->CVR = 0;
    // I want to activate processor clock and TICKINT and Systick (bit 0, 1, 2)
    SYST->CSR = (SYST->CSR & ~(7 << 0)) | 0x7; 
    
    bsp_tick = 0;

    return 0;
}

uint32_t bsp_timer_get_ticks(void){
        return bsp_tick;
}

void bsp_timer_delay_ms(uint32_t ms){
    uint32_t current_time = bsp_timer_get_ticks();    
    while ((bsp_tick - current_time) < ms);  
}

/* Handler SysTick */
void SysTick_Handler(void){
    bsp_tick++;
}
