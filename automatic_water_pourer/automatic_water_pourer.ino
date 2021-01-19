/*
 * automatic_water_pourer.ino
 * Measures the amount of water in a glass by using
 * an ultrasonic distance sensor.
 * 
 * Sahibjot Singh
 * January 18, 2020
 */


#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd{ 2, 3, 4, 5, 6, 7 };
Servo servo;
const byte echoPin = 8;
const byte trigPin = 9;
const byte servoPin = 10;
bool pourWater = false;

// Executes once, at the start
void setup() {
  lcd.begin(16, 2);
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  servo.attach(servoPin);
  servo.write(0);

  Serial.begin(9600);
}

// Loops infinitely
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / 58.2f;

  Serial.println(distance);
  
  lcd.clear();
  if (distance < 7) {
    lcd.print("Glass placed");
    if (pourWater) {
      for (byte i = 0; i < 120; ++i) {
        servo.write(i);
        delay(10);
        pourWater = false;
      }
    }
  } else {
    lcd.print("Glass removed");
    servo.write(0);
    pourWater = true;
  }
  
  delay(100);
}
