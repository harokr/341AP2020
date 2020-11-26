/*
  Reads an analog input on A0 and sends it out through the USB to a COM port generated when the Arduino is plugged into the computer


*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to


double sensorValue = 0;        // value read from the pot


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = (double)analogRead(analogInPin);

  // print the results to the Serial Monitor:

  Serial.println(sensorValue);
 

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(50);
}
