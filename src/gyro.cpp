#include "../include/gyro.h"
#include <arduino.h>
#include "Wire.h"

// MPU 6050 data sheet
// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

void Gyro::init()
{ 
  Wire.begin();                       //Begin I2C communication
  
  writeToRegistery(0x6B, 0x80);       // Write 1 to the DEVICE_RESET register
  delay(100);                         // 100 ms wait (defined in data sheet)

  writeToRegistery(0x6B, B00101000);  // Set CYCLE to 1, set SLEEP to 0, and set TEMP_DIS to 1 as staed in data sheet
  delay(100);
  writeToRegistery(0x6C, B11000111);  // Sets accelerometer frequencey to 40hz and put gyro into standby
}
 
int Gyro::FunctionsPitchRoll(double axisX, double axisY, double axisZ)
{
  double DataX, DataY, Value;
  DataX = axisX;
  DataY = (axisY * axisY) + (axisZ * axisZ); // A^2 + B^2 = C^2
  DataY = sqrt(DataY);                      
  
  Value = atan2(axisX, axisY); // Solve for angle between two planes
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
