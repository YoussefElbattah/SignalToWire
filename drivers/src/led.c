#include "led.h"
static bsp_gpio_cfg_t *cfg_led1, *cfg_led2, *cfg_led3;
int led_init(void){
    /* Initialize LED1 */
    cfg_led1->pin = LED1_PIN;
    cfg_led1->port = LED1_PORT;
    cfg_led1->speed = BSP_GPIO_SPEED_MEDIUM;
    cfg_led1->pull = BSP_GPIO_PULLUP;
    cfg_led1->af = BSP_GPIO_MODE_OUTPUT; 

    /* Initialize LED2 */
    cfg_led2->pin = LED2_PIN;
    cfg_led2->port = LED2_PORT;
    cfg_led2->speed = BSP_GPIO_SPEED_MEDIUM;
    cfg_led2->pull = BSP_GPIO_PULLUP;
    cfg_led2->af = BSP_GPIO_MODE_OUTPUT; 
    
    /* Initialize LED3 */
    cfg_led3->pin = LED3_PIN;
    cfg_led3->port = LED3_PORT;
    cfg_led3->speed = BSP_GPIO_SPEED_MEDIUM;
    cfg_led3->pull = BSP_GPIO_PULLUP;
    cfg_led3->af = BSP_GPIO_MODE_OUTPUT; 

    int ret = bsp_gpio_config(cfg_led1);
    if(ret != 0){
        return ret;
    }

    ret = bsp_gpio_config(cfg_led2);
    if(ret != 0){
        return ret;
    }

    ret = bsp_gpio_config(cfg_led3);
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