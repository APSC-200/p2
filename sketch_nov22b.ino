// Interfacing Arduino with DHT22 humidity and temperature sensor
 
// include LCD library code
#include <LiquidCrystal.h>
// include DHT library code
#include "DHT.h"
 
#define DHTPIN 8            // DHT22 data pin is connected to Arduino pin 8
 
// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
#define DHTTYPE DHT22       // DHT22 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
 
char temperature[] = "Temp = 00.0 C";
char humidity[]    = "RH   = 00.0 %";
void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  dht.begin();
}
 
void loop() {
  delay(1000);               // wait 1s between readings
  // Read humidity
  int RH = dht.readHumidity() * 10;
  //Read temperature in degree Celsius
  int Temp = dht.readTemperature() * 10;
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(RH) || isnan(Temp)) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 
  if(Temp < 0){
    temperature[6] = '-';
    Temp = abs(Temp);
  }
  else
    temperature[6] = ' ';
  temperature[7]   = (Temp / 100) % 10  + 48;
  temperature[8]   = (Temp / 10)  % 10  + 48;
  temperature[10]  =  Temp % 10 + 48;
  temperature[11]  = 223;        // Degree symbol ( °)
  if(RH >= 1000)
    humidity[6]    = '1';
  else
    humidity[6]    = ' ';
  humidity[7]      = (RH / 100) % 10 + 48;
  humidity[8]      = (RH / 10) % 10 + 48;
  humidity[10]     =  RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);
}
