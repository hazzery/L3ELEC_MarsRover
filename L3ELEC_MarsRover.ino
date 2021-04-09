#include <LiquidCrystal_I2C.h>
#include <Adafruit_GPS.h>
#include "include/magnetometer.h"
#include "include/coords.h"
#include "include/motors.h"
#include "include/units.h"
#include "include/robot.h"
#include "include/PID.h"

#define GPSSerial Serial
#define GPSECHO false

Adafruit_GPS GPS(&GPSSerial);//Define GPS at serial port
LiquidCrystal_I2C lcd(0x27,20,4);//Define LCD reselution as 16 x 2
Magnetometer mag(0x0d);
PID bearingPID(1.0, 0.0, 0.0);
Motor leftDrive(2, 3, 6);
Motor rightDrive(4, 5, 7);
Robot rover(&leftDrive, &rightDrive);

Coords startingPosition(-37.6774, 176.13032);
Coords finishingPosition(-37.67826, 176.12999);

double totalDistance = Coords::getDistance(startingPosition, finishingPosition);

// void initLCD();
// void updateLCD();

void setup()
{
  // initLCD();
  Serial.begin(115200);//Starts serial comunication with computer
  GPS.begin(9600);//Starts comuntication between GPS and Arduino

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);//Tell GPS to output the RMC and GGA data types
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);//Tell GPS to report antenna status

  delay(1000);

  GPSSerial.println(PMTK_Q_RELEASE);//Print release and version of GPS

  lcd.begin();//initialise LCD
  lcd.backlight();//Enable backlight

  lcd.setCursor(0,0);
  lcd.print("Lat: ");
  lcd.setCursor(0,1);
  lcd.print("Lon: ");
  lcd.setCursor(0,2);
  lcd.print("CuBr: ");
  lcd.setCursor(0,3);
  lcd.print("Br2F: ");

  rover.drive(255);
}

void loop()
{
 // updateLCD();

 char c = GPS.read();
 if (GPSECHO)
   if (c) Serial.print(c);
 if (GPS.newNMEAreceived())
 {
   Serial.print(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
   if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
     return; // we can fail to parse a sentence in which case we should just wait for another
 }
 
 Coords currentPosition (GPS.latitudeDegrees, GPS.longitudeDegrees);
 double bearingToFinish = Coords::getBearing(currentPosition, finishingPosition, degrees);
 double currentBearing = mag.getBearing(degrees);

 unsigned long timer;

 if (millis() - timer > 2000)
 {
   timer = millis(); // reset the timer
   
   lcd.setCursor(5, 0);
   lcd.print(GPS.latitude, 5);
   
   lcd.setCursor(18, 0);
   lcd.print(GPS.lat);
   
   lcd.setCursor(5, 1);
   lcd.print(GPS.longitude, 5);

   lcd.setCursor(18, 1);
   lcd.print(GPS.lon);

   lcd.setCursor(6, 2);
   lcd.print(currentBearing);

   lcd.setCursor(6, 3);
   lcd.print(bearingToFinish);
 }
 // bearingPID.calculate(currentBearing);
 // double motorOutput = bearingPID.output();
}
