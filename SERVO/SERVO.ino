#include <Servo.h>

Servo myServo;  // Create a servo object

void setup() {
    myServo.attach(9);  // Connect servo signal pin to D9
}

void loop() {
    myServo.write(0);   // Move servo to the longest left position (0°)
    delay(5000);        // Wait for 5 seconds

    myServo.write(180); // Move servo to the longest right position (180°)
    delay(5000);        // Wait for 5 seconds
}

