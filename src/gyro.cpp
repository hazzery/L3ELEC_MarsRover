#include "../include/gyro.h"
#include <arduino.h>
#include "Wire.h"

// MPU 6050 data sheet
// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

void Gyro::init()
{ 
  _address = 0x68; // Base address of MPU
  Wire.begin();
  // writeToRegistery(0x6B, 0);  // PWR_MGMT_1 register
  
  // This how I might do it
  
  writeToRegistery(0x6B, 0x80);     // Write 1 to the DEVICE_RESET register
  delay(100);                       // 100 ms wait (defined in data sheet)
  writeToRegistery(_address, 0x7);  // Write 1 to the 3 SIGNAL_PATH_RESET registers
  delay(100);                       // GYRO_RESET, ACCEL_RESET and TEMP_RESET
  writeToRegistery(0x6B, 0);        // Now wake
}
 
int Gyro::FunctionsPitchRoll(double axisX, double axisY, double axisZ)
{
  double DataX, DataY, Value;
  DataX = axisX;
  DataY = (axisY * axisY) + (axisZ * axisZ); // A^2 + B^2 = C^2
  DataY = sqrt(DataB);                      
  
  Value = atan2(DataA, DataB); // Solve for angle between two planes
  Value = Value * RAD_TO_DEG;
  
  return Value;
}

void Gyro::Functions()
{
  Wire.beginTransmission(_address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  Wire.requestFrom(_address, 6, true);  // request a total of 6 registers
  AccelerationX = Wire.read() << 8 | Wire.read(); // ACCEL_XOUT_H & ACCEL_XOUT_L     
  AccelerationY = Wire.read() << 8 | Wire.read();  
  AccelerationZ = Wire.read() << 8 | Wire.read();
}
