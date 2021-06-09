#include "../include/magnetometer.h"
#include "../include/I2CDevice.h"
#include "../include/units.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <math.h>
#include "Wire.h"

void Magnetometer::init()//Initialize magnetometer.
{
  delay(10);
  
  Wire.begin();//Start I2C communication for magnetometer.
 
  writeToRegistery(0x0b, 1);//Tell the magnetometer to run in continuous mode.
  writeToRegistery(0x09, 1); 
}

bool Magnetometer::ready()//Is the magnetometer ready?
{
  //Tell magnetometer we want to read from register 6.
  Wire.beginTransmission(_address);
  Wire.write(0x06);

  Wire.requestFrom(_address, 1);//Tell magnetometer we want 1 byte.
  byte readData = Wire.read() & 1;//Read the data from the magnetometer.

  Wire.endTransmission();
  return readData;
}

void Magnetometer::readRawData()//Gets raw xyz data from magnetometer.
{ 
  //Tell magnetometer to start reading from register zero.
  Wire.beginTransmission(_address);
  Wire.write(0x00);
  Wire.endTransmission();
  
  //Tell megnetometer we want 6 bytes.
  Wire.requestFrom(_address, (byte)6);

  x = (int16_t)(Wire.read() | Wire.read() << 8);//Save x ordinate.
  y = (int16_t)(Wire.read() | Wire.read() << 8);//Save y ordinate.
  z = (int16_t)(Wire.read() | Wire.read() << 8);//Save z ordinate.
}

void Magnetometer::calculateOffsets()
{
  //Set offset values to average of maximum and minimum values.
  offsetX = (maxX + minX) / 2;
  offsetY = (maxY + minY) / 2;
}

void Magnetometer::calibrate()
{
  const int calibrationLength = 10000;//Length of calibration - in ms.
  const int eepromAddress = 66;//Start address for EEPROM.

  unsigned long startTime = millis();//Time at start of calibration.
  
  bool calibrating = 1;
  byte startCal = 1;

  while (!ready());
	readRawData();

  //Set initial values to current magnetometer readings.
  maxX = minX = x;
  maxY = minY = y;

  while(calibrating)
  {
    if (ready())
    {
      readRawData();

      //Store maximum and minimum values from magnetometer.
      if (x > maxX) maxX = x;
      else if (x < minX) minX = x;
      if (y > maxY) maxY = y;
      else if (y < minY) minY = y;
    }
      
    //Time calculations.
    int timeDifference  = millis() - startTime;
    int secs = (int)((calibrationLength - timeDifference + 1000) / 1000);
    Serial.print("Calibrating, ");
    Serial.print((calibrationLength - timeDifference) / 1000);
    Serial.println(" secconds remaining.");
  
    if (secs == 0)//Calibration has finished.
    {
      calculateOffsets();
      calibrating = 0;

      //Store maximum and minimum values to permanent storage on Arduino.
      int EEAddr = eepromAddress;
      EEPROM.put(EEAddr, minX);
      EEAddr += sizeof(minX);
      EEPROM.put(EEAddr, maxX);
      EEAddr += sizeof(maxX);
      EEPROM.put(EEAddr, minY);
      EEAddr += sizeof(minY);
      EEPROM.put(EEAddr, maxY);
      EEAddr += sizeof(maxY);
      
      Serial.println("EEPROM Written");
    }
  
    delay(10);
  } //while(calibrating)
}

int Magnetometer::getX()
{ return x; }
int Magnetometer::getY()
{ return y; }
int Magnetometer::getZ()
{ return z; }

double Magnetometer::getBearing(AngleUnits angleUnit = radians)
{
  readRawData();

  //Calculate bearing between from magnetic north
  double angle = atan2((float)(x - offsetX),(float)(y - offsetY));
  double bearing = fmod(-angle + (TWO_PI), TWO_PI);

  if (angleUnit == radians)
    return bearing;
  else
    return bearing * (RAD_TO_DEG);
}
