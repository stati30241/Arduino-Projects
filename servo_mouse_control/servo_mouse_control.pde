/*
  servo_mouse_control.pde
  Sends the values for the angles of the servo
  motors via serial communication.
  
  Sahibjot Singh
  May 2021
*/


// Used to communicate via the serial port
import processing.serial.*;

Serial port;

// Executes once, at the start
void setup() {
  size(600, 600);                              // Sets the window size
  String portName = Serial.list()[0];          // Gets the port name
  port = new Serial(this, portName, 9600);     // Initializes the serial port
  delay(1000);
}

// Loops infinitely
void draw() {
  // Clears the window
  clear();
  
  // Gets the angles of the servos from the mouse coordinates
  int xServoAngle = (int)map(mouseX, 0, 600, 0, 180);
  int yServoAngle = (int)map(mouseY, 0, 600, 0, 180);
  
  // Writes the angles to the serial port
  port.write(String.valueOf(xServoAngle) + '\n'); println(xServoAngle);
  port.write(String.valueOf(yServoAngle) + '\n'); println(yServoAngle);
}
