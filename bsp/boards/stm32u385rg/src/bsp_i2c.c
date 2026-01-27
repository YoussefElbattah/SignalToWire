#include "bsp_i2c.h"


/* Registres I2C (privés, diffèrent selon familles STM32) */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} i2c_reg_t;

/* Mapping par carte :
   BSP_I2C_1 -> base address + clocks + pins AF (via bsp_gpio_config)
*/
