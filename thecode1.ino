#include <Adafruit_GPS.h>

#define GPSSerial Serial
#define GPSECHO false

Adafruit_GPS GPS(&GPSSerial);//Define GPS at serial port

void setup()
{
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
  char c = GPS.read();//Gets GPS character
  if (GPSECHO)
  {
    if (c)
      Serial.print(c);
  }

  if (GPS.newNMEAreceived())//If a new line of NMEA data has been recieved...
  {
    Serial.print(GPS.lastNMEA());//...print the last set of NMEA data..
    if (!GPS.parse(GPS.lastNMEA()))//...and if the last set of data will not pass...
      return;//...exit the loop.
  }

  if (millis() - timer > 1000)
  {
    timer = millis(); // reset the timer
    if (GPS.fix)
    {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4);
      Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4);
      Serial.println(GPS.lon);

      Serial.print("Speed (knots): ");
      Serial.println(GPS.speed);
      Serial.print("Angle: ");
      Serial.println(GPS.angle);
      Serial.print("Altitude: ");
      Serial.println(GPS.altitude);

      Serial.print("Satellites: ");
      Serial.println((int)GPS.satellites);
    }

  }
  delay(50);
}
