/* FSR simple testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
 
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int ledPin = 13;
int buzzerPin = 8;



 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  pinMode(ledPin, OUTPUT);
}
 
void loop(void) {


  fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (fsrReading < 3) {
    Serial.println(" - No pressure");
  digitalWrite(ledPin, LOW);
  delay(1000);
  
  
  } else if (fsrReading < 5) {
    Serial.println(" - Light touch");

    digitalWrite(ledPin, HIGH);
  delay(1000);
  
  } else if (fsrReading < 7) {
    Serial.println(" - Light squeeze");

        digitalWrite(ledPin, HIGH);
  delay(1000);
  
  } else if (fsrReading < 7) {
    Serial.println(" - Medium squeeze");

        digitalWrite(ledPin, HIGH);
  delay(1000);
  
  } else {
    Serial.println(" - Big squeeze");
  }
  delay(1000);
} 
