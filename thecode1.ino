#include <Adafruit_GPS.h>
#include <LiquidCrystal_I2C.h>

#define GPSSerial Serial
#define GPSECHO false

Adafruit_GPS GPS(&GPSSerial);//Define GPS at serial port
LiquidCrystal_I2C lcd(0x27,16,2);//Define LCD reselution as 16 x 2

void setup()
{
  lcd.begin();//initialise LCD
	lcd.backlight();//Enable backlight

  lcd.setCursor(0,0);
  lcd.print("Lat: ");
  lcd.setCursor(0,1);
  lcd.print("Lon: ");
  lcd.setCursor(0,2);
  lcd.print("Fix: ");
  lcd.setCursor(12,2);
  lcd.print("Qlt: ");
  lcd.setCursor(0,3);
  lcd.print("Sat: ");

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
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
    }
    lcd.setCursor(5, 0);
    lcd.print(GPS.latitude, 5);
    
    lcd.setCursor(18, 0);
    lcd.print(GPS.lat);
    
    lcd.setCursor(5, 1);
    lcd.print(GPS.longitude, 5);

    lcd.setCursor(18, 1);
    lcd.print(GPS.lon);

    lcd.setCursor(5, 2);
    lcd.print((int)GPS.fix);

    lcd.setCursor(18, 2);
    lcd.print((int)GPS.fixquality);

    lcd.setCursor(5, 3);
    lcd.print((int)GPS.satellites);
  }
  delay(50);
}
