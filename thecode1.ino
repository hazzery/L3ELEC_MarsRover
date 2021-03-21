#include <LiquidCrystal_I2C.h>
#include <Adafruit_GPS.h>
#include "magnetometer.h"
#include "coords.h"

#define GPSSerial Serial
#define GPSECHO false

Adafruit_GPS GPS(&GPSSerial);//Define GPS at serial port
LiquidCrystal_I2C lcd(0x27,16,2);//Define LCD reselution as 16 x 2
Magnetometer mag(0x0d);

Coords startingPosition(-37.6774, 176.13032);
Coords finishingPosition(-37.67826, 176.12999);

double totalDistance = Coords::getDistance(startingPosition, finishingPosition);

void initLCD();
void updateLCD();

void setup()
{
  initLCD();
  Serial.begin(115200);//Starts serial comunication with computer
  GPS.begin(9600);//Starts comuntication between GPS and Arduino

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);//Tell GPS to output the RMC and GGA data types
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);//Tell GPS to report antenna status

  delay(1000);

  GPSSerial.println(PMTK_Q_RELEASE);//Print release and version of GPS
}

void loop()
{
  updateLCD();

  Coords currentPosition (GPS.latitudeDegrees, GPS.longitudeDegrees);
  double bearingToFinish = Coords::getBearing(currentPosition, finishingPosition);
  double currentBearing = mag.getBearing();

  delay(1000);
}
