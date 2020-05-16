// 
// 
// 

#include "Joystic.h"

Joystic::Joystic(int xPin, int yPin) {
    this->xPin = xPin;
    this->yPin = yPin;
}
float Joystic::getX() {
    return (analogRead(xPin) - 512) / 512.f;
}
float Joystic::getY() {
    return (analogRead(yPin) - 512) / 512.f;
}
void Joystic::steup() {
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}
