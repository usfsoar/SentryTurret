#ifndef SOAR_SERVO_H
#define SOAR_SERVO_H

#include <ESP32Servo.h>

class SOAR_Servo {
public:
    explicit SOAR_Servo(int pin);
    void setup();
    void move(int startAngle, int endAngle);
    void autoMove(int endAngle);

private:
    Servo myservo;
    int servoPin;
    int currentDegrees;
};

#endif
