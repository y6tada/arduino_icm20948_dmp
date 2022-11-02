#include <SPI.h>

#define ICM20948_CS_PIN 12

static const uint8_t dmp3_image[] = {
#include "icm20948_img.dmp3a.h"
};

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  pinMode(ICM20948_CS_PIN, OUTPUT);
  digitalWrite(ICM20948_CS_PIN, HIGH);
  SPISettings _spisetting = SPISettings(7000000, MSBFIRST, SPI_MODE0);
  
  Serial.begin(115200);

  while (!Serial);
  Serial.println("program start");
  
  SPI.beginTransaction(_spisetting);
  digitalWrite(ICM20948_CS_PIN, LOW);
  uint8_t REG_SELECT_BANK0[] = {0x7F, 0x00};
  Serial.println(SPI.transfer(127));
  Serial.println(SPI.transfer(0));
  digitalWrite(ICM20948_CS_PIN, HIGH);
  SPI.endTransaction();

  SPI.beginTransaction(_spisetting);
  digitalWrite(ICM20948_CS_PIN, LOW);
  Serial.println(SPI.transfer(0x00 | 0x80));
  Serial.println(SPI.transfer(0x00));
  digitalWrite(ICM20948_CS_PIN, HIGH);
  SPI.endTransaction();
}

void loop() {
  // put your main code here, to run repeatedly:

}
