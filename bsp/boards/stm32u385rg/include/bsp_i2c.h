#ifndef BSP_I2C_H
#define BSP_I2C_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    BSP_I2C_1 = 1,
    BSP_I2C_2 = 2,
    BSP_I2C_3 = 3
} bsp_i2c_id_t;

typedef enum {
    BSP_I2C_SPEED_STANDARD_100K,
    BSP_I2C_SPEED_FAST_400K
} bsp_i2c_speed_t;

typedef enum {
    BSP_I2C_OK = 0,
    BSP_I2C_ERR_TIMEOUT = -1,
    BSP_I2C_ERR_NACK = -2,
    BSP_I2C_ERR_BUS = -3,
    BSP_I2C_ERR_PARAM = -4
} bsp_i2c_status_t;

typedef struct {
    bsp_i2c_id_t     id;
    bsp_i2c_speed_t  speed;
    uint32_t         timeout_ms;
} bsp_i2c_cfg_t;

/* API BSP I2C */
bsp_i2c_status_t bsp_i2c_init(const bsp_i2c_cfg_t *cfg);

bsp_i2c_status_t bsp_i2c_write(bsp_i2c_id_t id, uint8_t addr7,
                               const uint8_t *data, size_t len);

bsp_i2c_status_t bsp_i2c_read(bsp_i2c_id_t id, uint8_t addr7,
                              uint8_t *data, size_t len);

#endif /* BSP_I2C_H */