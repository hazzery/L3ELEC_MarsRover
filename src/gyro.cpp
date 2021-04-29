#include "../include/gyro.h"
#include <arduino.h>
#include "Wire.h"

Gyro::Gyro(uint8_t Address)
 : address(Address) {}

void Gyro::init()
{
  Wire.begin();

  Wire.beginTransmission(address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  delay(1000);
}
 

int Gyro::FunctionsPitchRoll(double A, double B, double C)
{
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * RAD_TO_DEG;
  
  return Value;
}

void Gyro::Functions()
{
  Wire.beginTransmission(address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  Wire.requestFrom(address, 6, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();      
  AcY = Wire.read() << 8 | Wire.read();  
  AcZ = Wire.read() << 8 | Wire.read();
}