/*
  Arduino2
*/
#include <Wire.h>

#define interruptPin_send 2
#define arduino1_address  1
#define arduino2_address  2

volatile short int interrupt_to_send = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(interruptPin_send, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_send), sendEvent, FALLING);

  Wire.begin(arduino2_address);
  Wire.onReceive(receiveEvent);  // register event

  Serial.begin(9600);
  Serial.print("Arduino2\r");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);  // do nothinig and wait for interrupt

  if (interrupt_to_send) {  // the actual sendEvent
    //detachInterrupt(interruptPin_send);
    Wire.beginTransmission(arduino1_address);  // transmit to device #1
    Wire.write("hiFromArd2\r");
    Wire.endTransmission();
    //attachInterrupt(digitalPinToInterrupt(interruptPin_send), sendEvent, FALLING);
    interrupt_to_send = 0;

  }
}
void sendEvent(void) {
  interrupt_to_send = 1;
}

void receiveEvent(void) {
  while (Wire.available()) {
    char data = Wire.read();
    Serial.print(data);
  }
}
