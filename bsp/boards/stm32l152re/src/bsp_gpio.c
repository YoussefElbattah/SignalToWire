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

static const uint32_t gpio_ahb_en_mask[] = {
    [BSP_GPIO_PORTA] = RCC_AHBENR_GPIOA_EN,
    [BSP_GPIO_PORTB] = RCC_AHBENR_GPIOB_EN,
    [BSP_GPIO_PORTC] = RCC_AHBENR_GPIOC_EN,
    [BSP_GPIO_PORTD] = RCC_AHBENR_GPIOD_EN,
    [BSP_GPIO_PORTE] = RCC_AHBENR_GPIOE_EN,
    [BSP_GPIO_PORTF] = RCC_AHBENR_GPIOF_EN,
    [BSP_GPIO_PORTG] = RCC_AHBENR_GPIOG_EN,
    [BSP_GPIO_PORTH] = RCC_AHBENR_GPIOH_EN,
};

static gpio_reg_t *bsp_gpio_get_regs(bsp_gpio_port_t port){
    
    gpio_reg_t *gpio;

    switch (port)
    {
    case BSP_GPIO_PORTA:
        gpio = (gpio_reg_t*)GPIOA_BASE;
        break;
    case BSP_GPIO_PORTB:
        gpio = (gpio_reg_t*)GPIOB_BASE;
        break;
    case BSP_GPIO_PORTC:
        gpio = (gpio_reg_t*)GPIOC_BASE;
        break;
    case BSP_GPIO_PORTD:
        gpio = (gpio_reg_t*)GPIOD_BASE;
        break;
    case BSP_GPIO_PORTE:
        gpio = (gpio_reg_t*)GPIOE_BASE;
        break;
    case BSP_GPIO_PORTH:
        gpio = (gpio_reg_t*)GPIOH_BASE;
        break;
    case BSP_GPIO_PORTF:
        gpio = (gpio_reg_t*)GPIOF_BASE;
        break;
    case BSP_GPIO_PORTG:
        gpio = (gpio_reg_t*)GPIOG_BASE;
        break;  
    default:
        return NULL;
        break;
    }
    return gpio;
}

int bsp_gpio_config(const bsp_gpio_cfg_t *cfg){
    int ret = 0;
    gpio_reg_t *gpio;

    if(cfg == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        goto exit;
    }

    if(cfg->pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        goto exit;
    }

    bsp_clock_enable_ahb(gpio_ahb_en_mask[cfg->port]);

    gpio = bsp_gpio_get_regs(cfg->port);
    if(gpio == NULL){
        return -1; // TODO : to change with Invalid error, error.h
    }

    gpio->MODER = (gpio->MODER & ~(3 << cfg->pin*2)) | (cfg->mode << cfg->pin*2);
    gpio->PUPDR = (gpio->PUPDR & ~(3 << cfg->pin*2)) | (cfg->pull << cfg->pin*2);
    gpio->OSPEEDR =  (gpio->OSPEEDR & ~(3 << cfg->pin*2)) | (cfg->speed << cfg->pin*2);
    if(cfg->mode == BSP_GPIO_MODE_AF){
        if(cfg->pin < 8)
            gpio->AFR[0] = (gpio->AFR[0] & ~(0xF << cfg->pin*4)) | (cfg->af << cfg->pin*4);
        else
            gpio->AFR[1] = (gpio->AFR[1] & ~(0xF << (cfg->pin - 8)*4)) | (cfg->af << (cfg->pin - 8)*4); 
    }
    exit:
        return ret;
}

int bsp_gpio_set(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *gpio;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        return ret;
    }
    gpio = bsp_gpio_get_regs(port);
    if(gpio == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        return ret;
    }

    gpio->BSRR = (1 << pin);

    return ret;
}

int bsp_gpio_clear(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *gpio;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        return ret;
    }
    gpio = bsp_gpio_get_regs(port);
    if(gpio == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        return ret;
    }
    gpio->BSRR = (1 << (pin + 16));

    return ret;
}

int bsp_gpio_toggle(bsp_gpio_port_t port, bsp_gpio_pin_t pin){
    int ret = 0;
    gpio_reg_t *gpio;

    if(pin > 15){
        ret = -2; // TODO : to change with Out_of_range error, error.h
        return ret;
    }
    gpio = bsp_gpio_get_regs(port);
    if(gpio == NULL){
        ret = -1; // TODO : to change with Invalid error, error.h
        return ret;
    }
    if(gpio->ODR & (1 << pin))
        gpio->BSRR = (1 << (pin + 16));
    else
         gpio->BSRR = (1 << pin);

    return ret;
}