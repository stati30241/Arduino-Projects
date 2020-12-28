/*
 * pin_lock.ino
 * Simple lock that can be unlocked using a specific
 * pin (password).
 * 
 * author: stati
 * youtube: https://www.youtube.com/channel/UC7Lx000LLDX6CU0qsyHGfQw
 * December 27, 2020
 */


#include <Servo.h>

byte buttonPins[4] = { 2, 3, 4, 5 };        // The pins of the buttons for entering the pin
byte resetButtonPin = 6;                    // The pin for reseting the value entered or locking the lock
byte greenLedPin = 7, redLedPin = 8;        // LED pins to tell whether or not it's locked
byte servoPin = 9;                          // The pin of the servo that acts as the lock
byte piezoPin = 10;                         // The pin of the piezo to make lock more user friendly

bool buttonValues[4];                       // The values returned by the pin input buttons
bool resetButtonValue;                      // The value returned by the reset button
bool locked = true;                         // Whether or not the it's locked
String pin = "2012";                        // The pin the user needs to enter to unlock the lock, can be as long as wanted
String userInput = "";                      // The pin entered by the user

Servo servoLock;

// Executes once, at the start
void setup() {
  // Sets the mode of the pin input buttons
  for (const byte& buttonPin : buttonPins) {
    pinMode(buttonPin, INPUT);
  }

  // Sets the mode of the rest if the pins
  pinMode(resetButtonPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  // Attaches the servo to the servo pin and puts it in the locked state
  servoLock.attach(servoPin);
  servoLock.write(0);

  // Starts Serial communication at port 9600 (for debugging purposes)
  Serial.begin(9600);
}

// Loops infinitely
void loop() {
  // Getting the states of the reset button
  if (resetButtonValue && !digitalRead(resetButtonPin)) {
    tone(piezoPin, 220);
    delay(500);
    noTone(piezoPin);
    userInput = "";

    if (!locked) locked = true;
  }
  resetButtonValue = digitalRead(resetButtonPin);

  // Getting the value of the pin input buttons
  for (byte i = 0; i < 4; ++i) {
    if (buttonValues[i] && !digitalRead(buttonPins[i])) {
      tone(piezoPin, 156);
      delay(100);
      noTone(piezoPin);
      userInput += String{ i };
    }
    buttonValues[i] = digitalRead(buttonPins[i]);
  }

  // Unlocking the lock
  if (userInput == pin && locked) {
    locked = false;
    tone(piezoPin, 123);
    delay(1000);
    noTone(piezoPin);
  }

  // Sets the LEDs and the servo according to the state of the lock
  if (locked) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    servoLock.write(0);
  } else {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    servoLock.write(90);
  }

  // Printing the user input to the serial port (for debugging purposes)
  Serial.print("User Input: ");
  Serial.println(userInput);
}
