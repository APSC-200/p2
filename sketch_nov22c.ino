#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include "DHT.h"


#define DHTPIN 8
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
}

void loop() {
  
  float tempF = ((1.8*(dht.readTemperature()))+32);
//Conversion equation retrieved from https://www.weather.gov/media/epz/wxcalc/tempConvert.pdf  

  float hum = dht.readHumidity();


// heat index formula: -42.379 + 2.04901523*T + 10.14333127*RH - .22475541*T*RH - .00683783*T*T - .05481717*RH*RH + .00122874*T*T*RH + .00085282*T*RH*RH - .00000199*T*T*RH*RH 
// retrieved from https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
  float hIndexF = (-42.379 + (2.04901523*tempF) + (10.14333127*hum) - (0.22475541*tempF*hum) - (0.00683783*tempF*tempF) - (0.05481717*hum*hum) + (0.00122874*tempF*tempF*hum) + (0.00085282*tempF*hum*hum) - (0.00000199*tempF*tempF*hum*hum));
  float otherHInd = -42.379 + (2.04901523*tempF) + (10.14333127*hum) - (0.22475541*tempF*hum) - (0.00683783*tempF*tempF) - (0.05481717*hum*hum) + (0.00122874*tempF*tempF*hum) + (0.00085282*tempF*hum*hum) - (0.00000199*tempF*tempF*hum*hum);
  float hIndexC = ((tempF - 32) / 9);
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("T:"); // Prints string "Temp." on the LCD
  lcd.print(dht.readTemperature); // Prints the temperature value from the sensor
  lcd.print("  H:");
  lcd.print(hum);
  lcd.setCursor(0,1);
  lcd.print("Heat Index:");
  lcd.print(hIndexC);
  delay(2000);
}
