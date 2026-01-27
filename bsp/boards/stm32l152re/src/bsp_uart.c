#include "bsp_uart.h"

/* Registres UART/USART (privés, à adapter par famille STM32) */
typedef struct {
    volatile uint32_t SR;     /* ou ISR selon MCU */
    volatile uint32_t DR;     /* ou RDR/TDR */
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;   /* optionnel selon MCU */
} usart_reg_t;

/* Table de mapping par carte :
   BSP_UART_1 -> base address + clocks + pins AF (via bsp_gpio_config)
*/
