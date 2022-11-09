#include "icm20948.h"

// Arduino SPI library setting
SPISettings icm20948_arduino_spi_setting = SPISettings(
    7000000,    // max speed of ICM20948 SPI clock frequency
    MSBFIRST,   // as datasheet
    SPI_MODE0   // as datasheet
);

icm_state_t icm20948_init_spi(void)
{
    SPI.begin();

    // If you are using pre-implemented SPI CS pin on the arduino board, CS pin should be
    // automatically controlled so you don't need to control CS pin manually.
    pinMode(ICM20948_CS_PIN, OUTPUT);
    digitalWrite(ICM20948_CS_PIN, HIGH);

    return icm_state_no_error;
}

icm_state_t icm20948_write_reg(uint8_t addr, uint8_t *buf_write, uint16_t len_buf_write)
{
    SPI.beginTransaction(icm20948_arduino_spi_setting);
    digitalWrite(ICM20948_CS_PIN, LOW);
    uint8_t REG_SELECT_BANK0[] = {0x7F, 0x00};
    Serial.println(SPI.transfer(127));
    Serial.println(SPI.transfer(0));
    digitalWrite(ICM20948_CS_PIN, HIGH);
    SPI.endTransaction();

    return icm_state_no_error;
}

icm_state_t icm20948_read_reg (uint8_t addr, uint8_t *buf_read, uint16_t len_buf_read)
{
    SPI.beginTransaction(icm20948_arduino_spi_setting);
    digitalWrite(ICM20948_CS_PIN, LOW);
    Serial.println(SPI.transfer(addr | 0x80));
    while (1)
    {
        if (len_buf_read == 0)
        {
            break;
        }
        --len_buf_read;
        *buf_read = SPI.transfer(0x00);
        ++buf_read;
    }
    
    
    Serial.println(SPI.transfer(addr | 0x80));
    Serial.println(SPI.transfer(0x00));
    digitalWrite(ICM20948_CS_PIN, HIGH);
    SPI.endTransaction();

    return icm_state_no_error;
}