#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIG_PIN 9
#define ECHO_PIN 10

// Height of sensor from the floor in cm
const float SENSOR_HEIGHT = 200.0;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Height Meter");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duration;
  float distance;
  float height;

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = duration * 0.0343 / 2;

  // Calculate person's height
  height = SENSOR_HEIGHT - distance;

  lcd.clear();

  if (height > 50 && height < 220) {
    lcd.setCursor(0, 0);
    lcd.print("Height:");

    lcd.setCursor(0, 1);
    lcd.print(height, 1);
    lcd.print(" cm");
  } 
  else {
    lcd.setCursor(0, 0);
    lcd.print("Stand Properly");
    lcd.setCursor(0, 1);
    lcd.print("Under Sensor");
  }

  delay(500);
}