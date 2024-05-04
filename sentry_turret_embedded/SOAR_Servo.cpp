#include "SOAR_Servo.h"

SOAR_Servo::SOAR_Servo(int pin) : servoPin(pin) {}

void SOAR_Servo::setup() {
    myservo.attach(servoPin);
    myservo.write(0);
    delay(500);
    currentDegrees = 0;
}

void SOAR_Servo::move(int startAngle, int endAngle) {
    if (startAngle < endAngle) {
        for (int pos = startAngle; pos <= endAngle; pos++) {
            myservo.write(pos);
            delay(15);
            currentDegrees = pos;
        }
    } else {
        for (int pos = startAngle; pos >= endAngle; pos--) {
            myservo.write(pos);
            delay(15);
            currentDegrees = pos;
        }
    }
}
void SOAR_Servo::autoMove(int endAngle){
  this->move(currentDegrees, endAngle);
}
