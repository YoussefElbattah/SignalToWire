#include "led.h"

int led_init(void){
    /* Initialize LED1 */
    bsp_gpio_cfg_t cfg_led1 = {
        .pin = LED1_PIN,
        .port = LED1_PORT,
        .mode = BSP_GPIO_MODE_OUTPUT,
        .speed = BSP_GPIO_SPEED_MEDIUM,
        .pull = BSP_GPIO_PULLUP,
        .af = BSP_GPIO_MODE_OUTPUT,
    };

    /* Initialize LED2 */
    bsp_gpio_cfg_t cfg_led2 = {
        .pin = LED2_PIN,
        .port = LED2_PORT,
        .mode = BSP_GPIO_MODE_OUTPUT,
        .speed = BSP_GPIO_SPEED_MEDIUM,
        .pull = BSP_GPIO_PULLUP,
        .af = BSP_GPIO_MODE_OUTPUT,
    };
    /* Initialize LED3 */
    bsp_gpio_cfg_t cfg_led3 = {
        .pin = LED3_PIN,
        .port = LED3_PORT,
        .mode = BSP_GPIO_MODE_OUTPUT,
        .speed = BSP_GPIO_SPEED_MEDIUM,
        .pull = BSP_GPIO_PULLUP,
        .af = BSP_GPIO_MODE_OUTPUT,
    }; 
    int ret = bsp_gpio_config(&cfg_led1);
    if(ret != 0){
        return ret;
    }

    ret = bsp_gpio_config(&cfg_led2);
    if(ret != 0){
        return ret;
    }

    ret = bsp_gpio_config(&cfg_led3);
    if(ret != 0){
        return ret;
    }

    return 0;
}

void led_on(led_id_t led_id){
    switch(led_id){
        case LED_USER1:
            bsp_gpio_set(LED1_PORT, LED1_PIN);
            break;
        case LED_USER2:
            bsp_gpio_set(LED2_PORT, LED2_PIN);
            break;
        case LED_USER3:
            bsp_gpio_set(LED3_PORT, LED3_PIN);
            break;
        default:
            break;
    }
}

void led_off(led_id_t led_id){
    switch(led_id){
        case LED_USER1:
            bsp_gpio_clear(LED1_PORT, LED1_PIN);
            break;
        case LED_USER2:
            bsp_gpio_clear(LED2_PORT, LED2_PIN);
            break;
        case LED_USER3:
            bsp_gpio_clear(LED3_PORT, LED3_PIN);
            break;
        default:
            break;
    }
}

void led_toggle(led_id_t led_id){
    switch(led_id){
        case LED_USER1:
            bsp_gpio_toggle(LED1_PORT, LED1_PIN);
            break;
        case LED_USER2:
            bsp_gpio_toggle(LED2_PORT, LED2_PIN);
            break;
        case LED_USER3:
            bsp_gpio_toggle(LED3_PORT, LED3_PIN);
            break;
        default:
            break;
    }
}