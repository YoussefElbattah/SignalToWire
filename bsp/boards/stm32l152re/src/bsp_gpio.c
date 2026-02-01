#include "bsp_gpio.h"
#include "bsp_clock.h"
#include <stddef.h>

/* Structures registres GPIO (privées) */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} gpio_reg_t;

static gpio_reg_t *bsp_gpio_get_regs(bsp_gpio_port_t port){
    
    gpio_reg_t *GPIO;

    switch (port)
    {
    case BSP_GPIO_PORTA:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOA_EN);
        GPIO = (gpio_reg_t*)GPIOA_BASE;
        break;
    case BSP_GPIO_PORTB:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOB_EN);
        GPIO = (gpio_reg_t*)GPIOB_BASE;
        break;
    case BSP_GPIO_PORTC:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOC_EN);
        GPIO = (gpio_reg_t*)GPIOC_BASE;
        break;
    case BSP_GPIO_PORTD:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOD_EN);
        GPIO = (gpio_reg_t*)GPIOD_BASE;
        break;
    case BSP_GPIO_PORTE:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOE_EN);
        GPIO = (gpio_reg_t*)GPIOE_BASE;
        break;
    case BSP_GPIO_PORTH:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOH_EN);
        GPIO = (gpio_reg_t*)GPIOH_BASE;
        break;
    case BSP_GPIO_PORTF:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOF_EN);
        GPIO = (gpio_reg_t*)GPIOF_BASE;
        break;
    case BSP_GPIO_PORTG:
        bsp_clock_enable_ahb(RCC_AHBENR_GPIOG_EN);
        GPIO = (gpio_reg_t*)GPIOG_BASE;
        break;  
    default:
        return NULL;
        break;
    }
    return GPIO;
}

int bsp_gpio_config(const bsp_gpio_cfg_t *cfg){
    int ret = 0;
    gpio_reg_t *GPIO;

    if(cfg == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }

    if(cfg->pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        goto exit;
    }

    GPIO = bsp_gpio_get_regs(cfg->port);
    if(GPIO == NULL){
        return -1; // TODO : to change with Invalid error, error.h
    }

    GPIO->MODER = (GPIO->MODER & ~(3 << cfg->pin*2)) | (cfg->mode << cfg->pin*2);
    GPIO->PUPDR = (GPIO->PUPDR & ~(3 << cfg->pin*2)) | (cfg->pull << cfg->pin*2);
    GPIO->OSPEEDR =  (GPIO->OSPEEDR & ~(3 << cfg->pin*2)) | (cfg->speed << cfg->pin*2);
    if(cfg->mode == BSP_GPIO_MODE_AF){
        if(cfg->pin < 8)
            GPIO->AFR[0] = (GPIO->AFR[0] & ~(0xF << cfg->pin*4)) | (cfg->af << cfg->pin*4);
        else
            GPIO->AFR[1] = (GPIO->AFR[1] & ~(0xF << (cfg->pin - 8)*4)) | (cfg->af << (cfg->pin - 8)*4); 
    }
    exit:
        return ret;
}

int bsp_gpio_set(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *GPIO;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        goto exit;
    }
    GPIO = bsp_gpio_get_regs(port);

    exit:
        return ret;
}

int bsp_gpio_clear(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *GPIO;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        goto exit;
    }
    GPIO = bsp_gpio_get_regs(port);
    if(GPIO == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }
    exit:
        return ret;
}

int bsp_gpio_toggle(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *GPIO;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        goto exit;
    }
    GPIO = bsp_gpio_get_regs(port);
    if(GPIO == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }

    exit:
        return ret;
}