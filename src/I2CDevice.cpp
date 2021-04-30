#include "../include/I2CDevice.h"

I2CDevice::I2CDevice()
 :address(0) {}

I2CDevice::I2CDevice(uint8_t addr)
 :address(addr) {}

void I2CDevice::writeToRegistery(uint8_t registryAddr, uint8_t dataByte)//Send data to specified register.
{
  Wire.beginTransmission(address);//Begin communication with magnetometer.
  Wire.write(registryAddr);//Tell magnetometer the register we want to write to.
  Wire.write(dataByte);//Write data to megnertometer register.
  Wire.endTransmission();//End communication with magnetometer.
}