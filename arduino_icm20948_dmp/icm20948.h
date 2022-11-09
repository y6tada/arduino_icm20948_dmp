#ifndef __ICM20948_H__
#define __ICM20948_H__

#include "Arduino.h"
#include "SPI.h"

typedef enum
{
    icm_state_no_error,
    icm_state_error
} icm_state_t;

#define ICM20948_CS_PIN 12

extern icm_state_t icm20948_init_spi(void);
extern icm_state_t icm20948_select_bank(uint8_t bank);
extern icm_state_t icm20948_write_reg(uint8_t addr, uint8_t *buf_write, uint16_t len_buf_write);
extern icm_state_t icm20948_read_reg (uint8_t addr, uint8_t *buf_read, uint16_t len_buf_read);

#endif /* __ICM20948_H__ */
