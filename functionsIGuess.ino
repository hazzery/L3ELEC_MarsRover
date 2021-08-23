// void initLCD()
// {
//   lcd.begin();//initialise LCD
//   lcd.backlight();//Enable backlight

//   lcd.setCursor(0,0);
//   lcd.print("Lat: ");
//   lcd.setCursor(0,1);
//   lcd.print("Lon: ");
//   lcd.setCursor(0,2);
//   lcd.print("Fix: ");
//   lcd.setCursor(12,2);
//   lcd.print("Qlt: ");
//   lcd.setCursor(0,3);
//   lcd.print("Sat: ");
// }

// void updateLCD()
// {
//     lcd.setCursor(5, 0);
//     lcd.print(GPS.latitudeDegrees, 5);
    
//     lcd.setCursor(18, 0);
//     lcd.print(GPS.lat);
    
//     lcd.setCursor(5, 1);
//     lcd.print(GPS.longitudeDegrees, 5);

//     lcd.setCursor(18, 1);
//     lcd.print(GPS.lon);

//     lcd.setCursor(5, 2);
//     lcd.print((int)GPS.fix);

//     lcd.setCursor(18, 2);
//     lcd.print((int)GPS.fixquality);

//     lcd.setCursor(5, 3);
//     lcd.print((int)GPS.satellites);
// }
// void rotateToBearing(int requiredBearing)
// {
//   bearingPID.setTarget(requiredBearing);

//   double currentBearing = mag.getBearing(degrees);//21.31° E  ± 0.35°  changing by  0.09° E per year

//   double motorPower = bearingPID.calculate(currentBearing);

//   rover.turn(motorPower);
// }