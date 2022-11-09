#include "icm20948.h"

static const uint8_t dmp3_image[] = {
#include "icm20948_img.dmp3a.h"
};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("serial established");

  uint8_t icm20948_error = icm20948_init_spi();
  Serial.print("exec icm20948_init_spi\t");
  Serial.println(icm20948_error);

  uint8_t tmp_addr = 0x7F;
  uint8_t tmp_buf[] = {0, 0,};
  uint16_t tmp_len = 2;
  icm20948_write_reg(tmp_addr, tmp_buf, tmp_len);
  tmp_addr = 0x00;
  icm20948_read_reg(tmp_addr, tmp_buf, tmp_len);
}

void loop() {
  // put your main code here, to run repeatedly:

}
