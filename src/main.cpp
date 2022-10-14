#include <Arduino.h>

#define TIMER_INTERRUPT_DEBUG       0
#define ISR_SERVO_DEBUG             0

#include "ESP8266_ISR_Servo.h"

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

#define PIN_ECHO 12 // D6
#define PIN_TRIGGER 13 // D7
#define PIN_SERVO 14 // D5

int servoIndex = -1;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIGGER, OUTPUT);
  delay(1000);
  servoIndex = ISR_Servo.setupServo(PIN_SERVO, MIN_MICROS, MAX_MICROS);
}

int tick = 0;

void loop() {
  long duration, distance;
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = ((float)(340 * duration) / 1000) / 2;

  if (distance < 300) {
    Serial.print("Duration - ");
    Serial.print(duration);
    Serial.print(", Distance - ");
    Serial.print(distance);
    Serial.println("mm");
  }

  ISR_Servo.setPosition(servoIndex, (tick * 10) % 180);
  tick = (tick + 1) % 10;

  delay(300);
}
