#ifndef BSP_UART_H
#define BSP_UART_H

#include <stdint.h>
#include <stddef.h>


#define RCC_APB2ENR_USART1_EN   (1 << 14)
#define RCC_APB1ENR_USART2_EN   (1 << 17)
#define RCC_APB1ENR_USART3_EN   (1 << 18)  
#define RCC_APB1ENR_USART4_EN   (1 << 19)
#define RCC_APB1ENR_USART5_EN   (1 << 20)

#define USART1_BASE     0x40013800
#define USART2_BASE     0x40004400
#define USART3_BASE     0x40004800
#define USART4_BASE     0x40004C00
#define USART5_BASE     0x40005000

typedef enum {
    BSP_UART_1 = 1,
    BSP_UART_2 = 2,
    BSP_UART_3 = 3,
    BSP_UART_4 = 4,
    BSP_UART_5 = 5
} bsp_uart_id_t;

typedef enum {
    BSP_UART_PARITY_NONE,
    BSP_UART_PARITY_EVEN,
    BSP_UART_PARITY_ODD
} bsp_uart_parity_t;

typedef enum {
    BSP_UART_STOPBITS_1,
    BSP_UART_STOPBITS_0_5,
    BSP_UART_STOPBITS_2,
    BSP_UART_STOPBITS_1_5
} bsp_uart_stopbits_t;

typedef enum {
    BSP_UART_OVERSAMPLING_16,
    BSP_UART_OVERSAMPLING_8
} bsp_uart_oversampling_t;

typedef enum {
    BSP_UART_DATABITS_8,
    BSP_UART_DATABITS_9
} bsp_uart_databits_t;

typedef struct {
    bsp_uart_id_t        id;
    bsp_uart_oversampling_t oversampling;
    uint32_t             baudrate;
    bsp_uart_databits_t  databits;
    bsp_uart_stopbits_t  stopbits;
    bsp_uart_parity_t    parity;
} bsp_uart_cfg_t;

/* API BSP UART */
int     bsp_uart_init(const bsp_uart_cfg_t *cfg);
int     bsp_uart_write(bsp_uart_id_t id, const uint8_t *buf, size_t len);
int     bsp_uart_read(bsp_uart_id_t id, uint8_t *buf, size_t len);
int     bsp_uart_write_byte(bsp_uart_id_t id, uint8_t byte);
int     bsp_uart_read_byte(bsp_uart_id_t id, uint8_t *byte);

#endif
