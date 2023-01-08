#include <Servo.h>
#include <Arduino.h>

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int MIN_DISTANCE = 0;  // minimum distance in cm
const int MAX_DISTANCE = 14;  // maximum distance in cm
const int NOTHING_DISTANCE = 15;  // distance at which there is nothing in front of the sensor

Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(11);
  servo2.attach(12);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // send a pulse to the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure the time it takes for the pulse to travel to the object and back
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // convert to cm
  Serial.println(distance);

  if (distance < MIN_DISTANCE || distance > NOTHING_DISTANCE) {
    // if there is nothing in front of the sensor or an object is too close,
    // move the servos to the 0% position
    servo1.write(0);
    servo2.write(0);
  } else if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
    // if the distance is within the specified range (0-30 cm),
    // map the distance to a servo position (0-180 degrees) and write it to the servos
    int servo_pos = map(distance, MIN_DISTANCE, MAX_DISTANCE, 180, 0);
    servo1.write(servo_pos);
    servo2.write(servo_pos);
    delay(400);
    delay(15);  // add a delay to make the movement smoother
  } else {
    // if the distance is greater than 30 cm, move the servos to the 100% position
    servo1.write(180);
    servo2.write(180);
    delay(200);
  }
}