#include <Servo.h>

Servo myservo;
const int SV_PIN = 6;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SV_PIN, OUTPUT);
  myservo.attach(SV_PIN, 500, 2400);
  // myservo.write(180);
}

void loop() {
  myservo.write(180);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  myservo.write(90);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
