#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "bsp_gpio.h"

#define LED1_PORT   BSP_GPIO_PORTA
#define LED1_PIN    BSP_GPIO_PIN_5
#define LED2_PORT   BSP_GPIO_PORTB
#define LED2_PIN    BSP_GPIO_PIN_0
#define LED3_PORT   BSP_GPIO_PORTC
#define LED3_PIN    BSP_GPIO_PIN_13

typedef enum {
    LED_USER1 = 1,
    LED_USER2 = 2,
    LED_USER3 = 3
} led_id_t;

int led_init(void);
void led_on(led_id_t led_id);
void led_off(led_id_t led_id);
void led_toggle(led_id_t led_id);

#endif /* LED_H */