// Joystic.h

#ifndef _JOYSTIC_h
#define _JOYSTIC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Joystic {
public:
    Joystic(int xPin, int yPin);
    float getX();
    float getY();

    void steup();
private:
    int xPin, yPin;
};

#endif

