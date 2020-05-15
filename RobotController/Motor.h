// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum MotorMode {
    CONTINUOUS,
    STEPS
};

class Motor {
public:
    Motor(int pulsePin, int dirPin, int enablePin, MotorMode motorMode = STEPS, float stepSize = 1.8f, float motorAngle = 1.f);

    void setSpeed(float rotationSpeed);
    void setRotation(float rotation);
    void setDir(bool reverse);

    float getRotation() const;
    float getSpeed() const;
    bool isIdle();

    void setup();
    void loop();

private:
    void doSteps();
    void doContinuous();
    void disableMotor();
    void enableMotor();
    bool doPulse(unsigned long stepPeriodmicroSec);

    float calcAngleDis(float angle1, float angle2) const;
    float normalize_angle(float angle) const;
    bool calcDirection() const;

    int pulsePin, dirPin, enablePin;
    
    const MotorMode motorMode;
    float rotation, desiredRotation, rotationSpeed;
    
    const int stepsPerRotation;
    const float stepSize, motorAngle;
    
    bool dirValue;
    bool pulseValue;
    bool isMotorIdle;
    unsigned long lastIdleTime;
    unsigned long lastHighTime;
};

#endif

