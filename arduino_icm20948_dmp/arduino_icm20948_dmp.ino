#include "icm20948.h"

static const uint8_t dmp3_image[] = {
#include "icm20948_img.dmp3a.h"
};

uint8_t tmp_addr = 0x2D;
uint8_t tmp_buf[14];
uint16_t tmp_len = 14;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("serial established");

  const uint8_t spi_ss_pin = 7;
  uint8_t icm20948_error = icm20948_init_spi(spi_ss_pin);
  Serial.print("exec icm20948_init_spi\t");
  Serial.println(icm20948_error);

  // Select bank 0
  uint8_t write_addr = 0x7F;
  uint8_t write_buf  = 0x00; 
  uint8_t write_len  = 1;
  icm20948_write_reg(write_addr, write_buf, write_len);

  // Disable I2C
  write_addr = 0x03;
  write_buf  = 1 << 4;
  write_len  = 1;
  icm20948_write_reg(write_addr, write_buf, write_len);

  // Disable duty-cycled mode
  write_addr = 0x05;
  write_buf  = 0x70;
  write_len  = 1;
  icm20948_write_reg(write_addr, write_buf, write_len);

  // Wakeup
  write_addr = 0x06;
  write_buf  = 0x01;
  write_len  = 1;
  icm20948_write_reg(write_addr, write_buf, write_len);
}

void loop() {
  // put your main code here, to run repeatedly:

  icm20948_write_reg(0x7F, 0x00, 1); // Select bank 0
  icm20948_read_reg(tmp_addr, tmp_buf, tmp_len);

  Serial.print("\n");
  for (int i = 0; i < tmp_len; ++i)
  {
    Serial.print(*(tmp_buf + i));
    Serial.print("\t");
  }
}
