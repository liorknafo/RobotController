// 
// 
// 

#include "Joystic.h"

Joystic::Joystic(int xPin, int yPin) {
    this->xPin = xPin;
    this->yPin = yPin;
}
float Joystic::getX() {
    return (min(analogRead(xPin), 1024) - 512) / 512.f;
}
float Joystic::getY() {
    return (min(analogRead(yPin), 1024) - 512) / 512.f;
}
void Joystic::steup() {
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}
