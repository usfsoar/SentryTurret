#include "Arduino.h"
#include "SOAR_Taser.h"

SOAR_Taser::SOAR_Taser(int pin) : taserPin(pin) {}

void SOAR_Taser::setup() {
    pinMode(taserPin, OUTPUT);
}

void SOAR_Taser::fire() {
    digitalWrite(taserPin, HIGH);
}

void SOAR_Taser::stop() {
    digitalWrite(taserPin, LOW);
}