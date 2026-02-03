#include "printk.h"
#include "bsp_gpio.h"
#include <stdarg.h>
#include <stdio.h>

#define PRINTK_BUF_SIZE 128

int uart_pin_config(void){
    int ret = 0;
    /* Configure UART2 TX Pin (PA2) */
    bsp_gpio_cfg_t cfg_uart2_tx = {
        .pin = BSP_GPIO_PIN_2,
        .port = BSP_GPIO_PORTA,
        .mode = BSP_GPIO_MODE_AF,
        .speed = BSP_GPIO_SPEED_HIGH,
        .pull = BSP_GPIO_NOPULL,
        .af = GPIO_AF_USART2,
    };

    /* Configure UART2 RX Pin (PA3) */
    bsp_gpio_cfg_t cfg_uart2_rx = {
        .pin = BSP_GPIO_PIN_3,
        .port = BSP_GPIO_PORTA,
        .mode = BSP_GPIO_MODE_AF,
        .speed = BSP_GPIO_SPEED_HIGH,
        .pull = BSP_GPIO_NOPULL,
        .af = GPIO_AF_USART2,
    };

    ret = bsp_gpio_config(&cfg_uart2_tx);
    if (ret != 0)
    {
        return ret;
    }
    ret = bsp_gpio_config(&cfg_uart2_rx);
    if (ret != 0)
    {
        return ret;
    }
    return ret;
}
int printk_init(void){
    int ret = 0;
    bsp_uart_cfg_t uart_cfg;

    uart_cfg.id = BSP_UART_2;
    uart_cfg.baudrate = 115200;
    uart_cfg.databits = BSP_UART_DATABITS_8;
    uart_cfg.stopbits = BSP_UART_STOPBITS_1;
    uart_cfg.parity = BSP_UART_PARITY_NONE;
    uart_cfg.oversampling = BSP_UART_OVERSAMPLING_16;

    ret = bsp_uart_init(&uart_cfg);
    if (ret != 0)
    {
        return ret;
    }

    ret = uart_pin_config();
    return ret;
}

int printk(const char *fmt, ...)
{
    char buf[PRINTK_BUF_SIZE];
    va_list args;

    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    if (len < 0)
        return len;

    if (len > PRINTK_BUF_SIZE)
        len = PRINTK_BUF_SIZE;

    return bsp_uart_write(BSP_UART_2, (uint8_t *)buf, len);
}

int uart_read(uint8_t *buf, size_t len){
    return bsp_uart_read(BSP_UART_2, buf, len);
}