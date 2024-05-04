#include "SOAR_Servo.h"

SOAR_Servo myServo(A0);

void setup() {
    myServo.setup();
}

void loop() {
    myServo.move(0, 60);  // Move from 0 to 60 degrees
    myServo.move(60, 0);  // Move back from 60 to 0 degrees
}
