#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "bsp_clock.h"
#include "bsp_timer.h"
#include <stdint.h>

#define TIMEOUT_MS 5000

typedef struct {
    volatile uint32_t SR;     
    volatile uint32_t DR;     
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;   
} usart_reg_t;

static const uint32_t uart_apbx_en_mask[] = {
    [BSP_UART_1] = RCC_APB2ENR_USART1_EN,
    [BSP_UART_2] = RCC_APB1ENR_USART2_EN,
    [BSP_UART_3] = RCC_APB1ENR_USART3_EN,
    [BSP_UART_4] = RCC_APB1ENR_USART4_EN,
    [BSP_UART_5] = RCC_APB1ENR_USART5_EN,
};

static usart_reg_t *bsp_uart_get_regs(bsp_uart_id_t id){
    
    usart_reg_t *uart;

    switch (id)
    {
    case BSP_UART_1:
        uart = (usart_reg_t*)USART1_BASE;
        break;
    case BSP_UART_2:
        uart = (usart_reg_t*)USART2_BASE;
        break;
    case BSP_UART_3:
        uart = (usart_reg_t*)USART3_BASE;
        break;
    case BSP_UART_4:
        uart = (usart_reg_t*)USART4_BASE;
        break;
    case BSP_UART_5:
        uart = (usart_reg_t*)USART5_BASE;
        break;
    default:
        uart = NULL;
        break;
    }
    return uart;
}

void bsp_clock_enable_apbx(bsp_uart_id_t id, uint32_t *freq){
    switch (id)
    {
    case BSP_UART_1:
        bsp_clock_enable_apb2(uart_apbx_en_mask[id]);
        *freq = bsp_clock_get_apb2_hz();
        break;
    
    default: /* USART2, USART3, USART4, USART5 */
        bsp_clock_enable_apb1(uart_apbx_en_mask[id]);
        *freq = bsp_clock_get_apb1_hz();
        break;
    }
}


int bsp_uart_init(const bsp_uart_cfg_t *cfg){
    usart_reg_t *uart;

    int ret = 0;
    uint32_t periph_clk;
    if(cfg == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }
    bsp_clock_enable_apbx(cfg->id, &periph_clk);
    
    uart = bsp_uart_get_regs(cfg->id);
    if(uart == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }
    /* Configuration baudrate */
    // implement baudrate calculation based on peripheral clock
    uart->CR1 &= ~(1 << 13); // Disable USART before configuration
    uint32_t over, div, mantissa, fraction;
    div = periph_clk / cfg->baudrate;
    over = cfg->oversampling == BSP_UART_OVERSAMPLING_8 ? 8 : 16;

    mantissa = div / over;
    fraction = div - (mantissa * over);

    if (cfg->oversampling)
        fraction &= 0x07;

    uart->BRR = (mantissa << 4) | fraction;

    uart->CR1 |= (1 << 13); // Re-enable USART

    /* Configuration databits, stopbits, parity */
    uart->CR1 = (uart->CR1 & ~(1 << 12)) | (cfg->databits << 12);
    uart->CR1 = (uart->CR1 & ~(1 << 15)) | (cfg->oversampling << 15); // Set oversampling 
    uart->CR1 = (uart->CR1 & ~(1 << 9)) | (cfg->parity << 9); // Set parity
    uart->CR2 = (uart->CR2 & ~(3 << 12)) | (cfg->stopbits << 12); // Set stop bits
    uart->CR1 |= (1 << 3) | (1 << 2); // Enable transmitter and receiver

    exit:
        return ret;
}
int bsp_uart_write(bsp_uart_id_t id, const uint8_t *buf, size_t len){
    usart_reg_t *uart;
    uart = bsp_uart_get_regs(id);
    if(uart == NULL){
        return -1; // TODO : to change with Invalid error, error.h
    }

    for(size_t i = 0; i < len; i++){
        uint32_t systick = bsp_timer_get_ticks();
        while(!(uart->SR & (1 << 7))){
            if((bsp_timer_get_ticks() - systick) > TIMEOUT_MS){
                return -2; // TODO : to change with Timeout error, error.h
            }
        }
        uart->DR = (buf[i] & 0xFF);
    }
    return 0;
}
int bsp_uart_read(bsp_uart_id_t id, uint8_t *buf, size_t len){
    usart_reg_t *uart;
    uart = bsp_uart_get_regs(id);
    if(uart == NULL){
        return -1; // TODO : to change with Invalid error, error.h
    }
    for(size_t i = 0; i < len; i++){
        uint32_t systick = bsp_timer_get_ticks();
        while(!(uart->SR & (1 << 5))){
            if((bsp_timer_get_ticks() - systick) > TIMEOUT_MS){
                return -2; // TODO : to change with Timeout error, error.h
            }
        }
        buf[i] = (uint8_t)(uart->DR & 0xFF);
    }
    return 0;
}

int bsp_uart_write_byte(bsp_uart_id_t id, uint8_t byte){
    usart_reg_t *uart;
    uart = bsp_uart_get_regs(id);
    if(uart == NULL){
        return -1; // TODO : to change with Invalid error, error.h
    }
    uint32_t systick = bsp_timer_get_ticks();
    while(!(uart->SR & (1 << 7))){
        if((bsp_timer_get_ticks() - systick) > TIMEOUT_MS){
            return -2; // TODO : to change with Timeout error, error.h
        }
    }
    uart->DR = (byte & 0xFF);
    return 0;
}