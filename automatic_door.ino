#include <Servo.h>

Servo doorServo;

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);  // Door initially closed

  Serial.begin(9600);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  return duration * 0.0343 / 2;
}

void loop() {
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= 20) {
    // Open door
    doorServo.write(90);
    delay(3000);
  } 
  else {
    // Close door
    doorServo.write(0);
  }

  delay(100);
}