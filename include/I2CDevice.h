#pragma once
#include <arduino.h>

class I2CDevice
{
  public:
    I2CDevice();
    I2CDevice(uint8_t Address);

  protected:
    void writeToRegistery(uint8_t registryAddr, uint8_t dataByte);
    uint8_t address;
};