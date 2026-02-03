#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdint.h>

#define GPIOA_BASE  0x40020000
#define GPIOB_BASE  0x40020400
#define GPIOC_BASE  0x40020800
#define GPIOD_BASE  0x40020C00
#define GPIOE_BASE  0x40021000
#define GPIOF_BASE  0x40021400
#define GPIOG_BASE  0x40021800
#define GPIOH_BASE  0x40021C00

#define RCC_AHBENR_GPIOA_EN    (1 << 0)
#define RCC_AHBENR_GPIOB_EN    (1 << 1)
#define RCC_AHBENR_GPIOC_EN    (1 << 2)
#define RCC_AHBENR_GPIOD_EN    (1 << 3)
#define RCC_AHBENR_GPIOE_EN    (1 << 4)
#define RCC_AHBENR_GPIOH_EN    (1 << 5)
#define RCC_AHBENR_GPIOF_EN    (1 << 6)
#define RCC_AHBENR_GPIOG_EN    (1 << 7)

/* Identifiants ports BSP */
typedef enum {
    BSP_GPIO_PORTA,
    BSP_GPIO_PORTB,
    BSP_GPIO_PORTC,
    BSP_GPIO_PORTD,
    BSP_GPIO_PORTE,
    BSP_GPIO_PORTH,
    BSP_GPIO_PORTF,
    BSP_GPIO_PORTG
} bsp_gpio_port_t;

/* Identifiants pins BSP */
typedef enum {
    BSP_GPIO_PIN_0,
    BSP_GPIO_PIN_1,
    BSP_GPIO_PIN_2,
    BSP_GPIO_PIN_3,
    BSP_GPIO_PIN_4,
    BSP_GPIO_PIN_5,
    BSP_GPIO_PIN_6,
    BSP_GPIO_PIN_7,
    BSP_GPIO_PIN_8,
    BSP_GPIO_PIN_9,
    BSP_GPIO_PIN_10,
    BSP_GPIO_PIN_11,
    BSP_GPIO_PIN_12,
    BSP_GPIO_PIN_13,
    BSP_GPIO_PIN_14,
    BSP_GPIO_PIN_15
} bsp_gpio_pin_t;

/* Modes GPIO */
typedef enum {
    BSP_GPIO_MODE_INPUT,
    BSP_GPIO_MODE_OUTPUT,
    BSP_GPIO_MODE_AF,
    BSP_GPIO_MODE_ANALOG
} bsp_gpio_mode_t;

/* Pull-up / pull-down */
typedef enum {
    BSP_GPIO_NOPULL,
    BSP_GPIO_PULLUP,
    BSP_GPIO_PULLDOWN
} bsp_gpio_pull_t;

/* Vitesse */
typedef enum {
    BSP_GPIO_SPEED_LOW,
    BSP_GPIO_SPEED_MEDIUM,
    BSP_GPIO_SPEED_HIGH
} bsp_gpio_speed_t;

/* Configuration GPIO complète */
typedef struct {
    bsp_gpio_port_t  port;
    bsp_gpio_pin_t   pin;
    bsp_gpio_mode_t  mode;
    bsp_gpio_pull_t  pull;
    bsp_gpio_speed_t speed;
    uint8_t          af;    /* 0 si non AF */
} bsp_gpio_cfg_t;

/* API BSP GPIO */
int  bsp_gpio_init(void);
int  bsp_gpio_config(const bsp_gpio_cfg_t *cfg);
int bsp_gpio_set(bsp_gpio_port_t port, bsp_gpio_pin_t pin);
int bsp_gpio_clear(bsp_gpio_port_t port, bsp_gpio_pin_t pin);
int bsp_gpio_toggle(bsp_gpio_port_t port, bsp_gpio_pin_t pin);

#endif
/* BSP_GPIO_H */