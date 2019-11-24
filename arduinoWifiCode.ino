#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include "arduino_secrets.h"
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

#include "DHT.h"
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


int status = WL_IDLE_STATUS;
 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char serverAddress[] = "130.15.85.65";  // server address
int port = 80;
WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

int chk;
int inputPin = 9;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
float temp; //Stores temperature value


void setup() {
    // check for the WiFi module:
    dht.begin();
  lcd.begin(16,2);
  Serial.begin(9600);
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
         // declare LED as output
  
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
 pinMode(inputPin, INPUT);
   // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display

}

void loop() {
  // put your main code here, to run repeatedly:
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) { 
    // check if the input is HIGH
    
   
     //Add HI here if true call wifipost
  float tempF = ((1.8*(dht.readTemperature()))+32);
  float hum = dht.readHumidity();
heatIndex(tempF, hum);


     
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    
    if (pirState == HIGH){
     
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }




}

void heatIndex(float tempF, float hum){
   float hIndexF = (-42.379 + (2.04901523*tempF) + (10.14333127*hum) - (0.22475541*tempF*hum) - (0.00683783*tempF*tempF) - (0.05481717*hum*hum) + (0.00122874*tempF*tempF*hum) + (0.00085282*tempF*hum*hum) - (0.00000199*tempF*tempF*hum*hum));
  float otherHInd = -42.379 + (2.04901523*tempF) + (10.14333127*hum) - (0.22475541*tempF*hum) - (0.00683783*tempF*tempF) - (0.05481717*hum*hum) + (0.00122874*tempF*tempF*hum) + (0.00085282*tempF*hum*hum) - (0.00000199*tempF*tempF*hum*hum);
  float hIndexC = ((tempF - 32) / 9);
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("T:"); // Prints string "Temp." on the LCD
  lcd.print(dht.readTemperature()); // Prints the temperature value from the sensor
  lcd.print("  H:");
  lcd.print(hum);
  lcd.setCursor(0,1);
  lcd.print("Heat Index:");
  lcd.print(hIndexC);
  if(hIndexC > 40){
    wifiPost(9, 1, "Trigger12", "Trigger2", "Trigger3");
  }
}

//function to write post request to server
void wifiPost(int groupNum, int alertVar, String Trigger_1Var, String Trigger_2Var, String Trigger_3Var){
  int alert = (groupNum*10)+alertVar;
  
  //Post Request
  String postLine ="http://130.15.85.65/data.php?";
  Serial.println("making POST request");
  // Post request format ("serverLocation.php?Alert="+alertVar+"&Trigger_1="+Trigger_1Var+"&Trigger_2="+Trigger_2Var+"&Trigger_3="+Trigger_3Var)
  //"http://130.15.85.65/data.php?Alert=2&Trigger_1=Temp32&Trigger_2=PersonYes&Trigger_3=MotionYes"
  postLine += F("Alert=");
  postLine += alert;
  postLine += F("&Trigger_1=");
  postLine += Trigger_1Var;
  postLine += F("&Trigger_2=");
  postLine += Trigger_2Var;
  postLine += F("&Trigger_3=");
  postLine += Trigger_3Var;
  Serial.println(postLine);
  client.post(postLine);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
 
}
