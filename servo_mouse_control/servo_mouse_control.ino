/*
  servo_mouse_control.ino
  Simple program to control servo motors using an
  arduino mega 2560 and the processing enviroment.

  Sahibjot Singh
  May 2021
*/


#include <Servo.h> // Included to write to the servos

// Global variables
Servo xServo;
Servo yServo;
int xServoAngle;
int yServoAngle;

// Executes once, at the start
void setup() {
  // Initializes the servo pins and writes 0 to them
  xServo.attach(2);
  yServo.attach(3);
  xServo.write(0);
  yServo.write(0);

  // Begins serial communication
  Serial.begin(9600);
}

// Loops infinitely
void loop() {
  // Gets the values from the processing serial
  if (Serial.available()){
    xServoAngle = Serial.parseInt();
    yServoAngle = Serial.parseInt();
  }

  // Wrtes the angles to the corresponding servos
  xServo.write(xServoAngle);
  yServo.write(yServoAngle);
}
