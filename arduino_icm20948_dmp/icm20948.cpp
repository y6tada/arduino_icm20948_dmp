#include "icm20948.h"

// Arduino SPI library setting
SPISettings icm20948_arduino_spi_setting = SPISettings(
    7000000,    // max speed of ICM20948 SPI clock frequency
    MSBFIRST,   // as datasheet
    SPI_MODE0   // as datasheet
);

icm_state_t icm20948_init_spi(uint8_t _spi_cs_pin)
{
    SPI.begin();

    spi_cs_pin = _spi_cs_pin;

    // If you are using pre-implemented SPI CS pin on the arduino board, CS pin should be
    // automatically controlled so you don't need to control CS pin manually.
    pinMode(spi_cs_pin, OUTPUT);
    digitalWrite(spi_cs_pin, HIGH);

    return icm_state_ok;
}

icm_state_t icm20948_write_reg(uint8_t addr, uint8_t *buf_write, uint16_t len_buf_write)
{
    // SPI Hardware Kickstart
    SPI.beginTransaction(icm20948_arduino_spi_setting);
    SPI.transfer(0x00);
    SPI.endTransaction();

    SPI.beginTransaction(icm20948_arduino_spi_setting);
    digitalWrite(spi_cs_pin, LOW);

    SPI.transfer(((addr & 0x7F) | 0x00));
    for (int i = 0; i < len_buf_write; ++i)
    {
        SPI.transfer(*(buf_write + i));
    }
    digitalWrite(spi_cs_pin, HIGH);
    SPI.endTransaction();

    return icm_state_ok;
}

icm_state_t icm20948_read_reg (uint8_t addr, uint8_t *buf_read, uint16_t len_buf_read)
{
    // SPI Hardware Kickstart
    SPI.beginTransaction(icm20948_arduino_spi_setting);
    SPI.transfer(0x00);
    SPI.endTransaction();

    SPI.beginTransaction(icm20948_arduino_spi_setting);
    digitalWrite(spi_cs_pin, LOW);
    
    SPI.transfer(((addr & 0x7F) | 0x80));
    for (int i = 0; i < len_buf_read; ++i)
    {
        *(buf_read + i) = SPI.transfer(0x00);
    }
    
    digitalWrite(spi_cs_pin, HIGH);
    SPI.endTransaction();

    return icm_state_ok;
}