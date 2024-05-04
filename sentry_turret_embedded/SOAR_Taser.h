#ifndef SOAR_TASER_H
#define SOAR_TASER_H
class SOAR_Taser {
public:
    SOAR_Taser(int pin);
    void setup();
    void fire();
    void stop();
private:
    int taserPin;
};
#endif