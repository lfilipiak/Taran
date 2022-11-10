/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Wire library for I2C
#include <Wire.h>

// LED on pin 13
const int ledPin = 13;

void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x2);

  // Call receiveEvent when data received
  Wire.onReceive(receiveEvent);

  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) {  // loop through all but the last
    char c = Wire.read();     // receive byte as a character
    digitalWrite(ledPin, c);
    if (c == 1) requestEvent("OFF");
    else requestEvent("ON");
  }
}

void requestEvent(char *x) {
  Wire.beginTransmission(0x2);
  Wire.write(x);
  Wire.endTransmission();
}
void loop() {
  delay(100);
}