#include <LiquidCrystal_I2C.h>
#include <Adafruit_GPS.h>
#include "include/magnetometer.h"
#include "include/coords.h"
#include "include/motors.h"
#include "include/units.h"
#include "include/robot.h"
#include "include/PID.h"

// #define GPSSerial Serial1
// #define GPSECHO false

// Adafruit_GPS GPS(&GPSSerial);//Define GPS at serial port

Magnetometer mag(0x0d);
PID bearingPID(1.0, 0.0, 0.0);
PID distancePID(1.0, 0.0, 0.0);
Motor leftDrive(2, 3, 6);
Motor rightDrive(4, 5, 7);
Robot rover(&leftDrive, &rightDrive);

Coords startingPosition(-37.6774, 176.13032);
Coords finishingPosition(-37.67826, 176.12999);

double totalDistance = Coords::getDistance(startingPosition, finishingPosition);

double requiredBearing = 180;

void setup()
{
  Serial.begin(115200);//Starts serial comunication with computer
  mag.init();
  // GPS.begin(9600);//Starts comuntication between GPS and Arduino

  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);//Tell GPS to output the RMC and GGA data types
  // GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // GPS.sendCommand(PGCMD_ANTENNA);//Tell GPS to report antenna status

  // delay(1000);

  // GPSSerial.println(PMTK_Q_RELEASE);//Print release and version of GPS
}

void loop()
{
  double currentBearing = mag.getBearing(degrees);
  //21.31° E  ± 0.35°  changing by  0.09° E per year

  Serial.print("Current: ");
  Serial.println(currentBearing);

  bearingPID.setTarget(180);
  bearingPID.calculate(currentBearing);
  double motorPower = bearingPID.output();

  Serial.print("_Output: ");
  Serial.println(motorPower);

  Serial.println("");
  // Serial.print("x: ");
  // Serial.println(mag.getX());
  // Serial.print("y: ");
  // Serial.println(mag.getY());
  // Serial.print("z: ");
  // Serial.println(mag.getZ());

  delay(50);
}