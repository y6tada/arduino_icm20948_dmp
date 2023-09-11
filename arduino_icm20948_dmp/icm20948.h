#ifndef __ICM20948_H__
#define __ICM20948_H__

#include "Arduino.h"
#include "SPI.h"

typedef enum
{
    icm_state_ok,
    icm_state_error
} icm_state_t;

#define ICM20948_CS_PIN 12

extern icm_state_t icm20948_init_spi(uint8_t _spi_ss_pin);
extern icm_state_t icm20948_select_bank(uint8_t bank);
extern icm_state_t icm20948_write_reg(uint8_t addr, uint8_t *buf_write, uint16_t len_buf_write);
extern icm_state_t icm20948_read_reg (uint8_t addr, uint8_t *buf_read, uint16_t len_buf_read);

static uint8_t spi_cs_pin = 0;

#endif /* __ICM20948_H__ */
