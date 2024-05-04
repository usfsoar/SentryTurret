#include "SOAR_Servo.h"

SOAR_Servo::SOAR_Servo(int pin) : servoPin(pin) {}

void SOAR_Servo::setup() {
    myservo.attach(servoPin);
}

void SOAR_Servo::move(int startAngle, int endAngle) {
    if (startAngle < endAngle) {
        for (int pos = startAngle; pos <= endAngle; pos++) {
            myservo.write(pos);
            delay(15);
        }
    } else {
        for (int pos = startAngle; pos >= endAngle; pos--) {
            myservo.write(pos);
            delay(15);
        }
    }
}
