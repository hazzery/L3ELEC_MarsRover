#pragma once

#include <Arduino.h>
#include "I2CDevice.h"
#include "units.h"

class Magnetometer : public I2CDevice
{
  using I2CDevice::I2CDevice;
  using I2CDevice::writeToRegistery;

  private:
    int x, maxX, minX, offsetX;
    int y, maxY, minY, offsetY;
    int z, maxZ, minZ, offsetZ;
    
  public:
    void init();
    bool ready();
    void readRawData();
    void calculateOffsets();
    void calibrate();
    
    int getX();
    int getY();
    int getZ();

    double getBearing(AngleUnits angleUnit = radians);
};
