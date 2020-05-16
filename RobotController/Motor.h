// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class Motor {
public:
    Motor(int pulsePin, int dirPin, int enablePin, float stepSize = 1.8f, float motorAngle = 1.f);

    void setSpeed(float rotationSpeed);
    float getSpeed() const;

    bool isIdle();

    virtual void setup();
    virtual void loop() = 0;

private:
    unsigned long lastIdleTime;
    unsigned long lastHighTime;

    int pulsePin, dirPin, enablePin;
    
    float rotationSpeed;
    
    bool dirValue;
    bool pulseValue;
    bool isMotorIdle;

protected:
    bool doPulse(unsigned long stepPeriodmicroSec);
    void disableMotor();
    void enableMotor();
    void setDir(bool);

    const int stepsPerRotation;
    const float stepSize, motorAngle;
};


class MotorSteps : public Motor {
public:
    MotorSteps(int pulsePin, int dirPin, int enablePin, float stepSize = 1.8f, float motorAngle = 1.f);

    void move(float angle);

    virtual void loop() override;

//private:
    int steps_to_go;
};

#endif

