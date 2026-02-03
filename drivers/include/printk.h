#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>
#include "bsp_uart.h"

/* Alternante function define */
#define GPIO_AF_USART1    7
#define GPIO_AF_USART2    7
#define GPIO_AF_USART3    7
#define GPIO_AF_USART4    8
#define GPIO_AF_USART5    8

int printk_init(void);
int printk(const char *fmt, ...);
int uart_read(uint8_t *buf, size_t len);


#endif /* UART_H */