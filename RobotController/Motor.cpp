// 
// 
// 

#include "Motor.h"

Motor::Motor(int pulsePin, int dirPin, int enablePin, float stepSize, float motorAngle) :
	stepsPerRotation((360.00 / stepSize) / motorAngle), stepSize(stepSize), motorAngle(motorAngle) {
	this->pulsePin = pulsePin;
	this->dirPin = dirPin;
	this->enablePin = enablePin;
	
	this->rotationSpeed = 0;
	this->dirValue = false;
	
	this->lastIdleTime = 0;
	this->lastHighTime = 0;
	this->pulseValue = false;
}

void Motor::setSpeed(float rotationSpeed) {
	this->rotationSpeed = rotationSpeed;
}


void Motor::setup() {
	pinMode(pulsePin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enablePin, OUTPUT);
}

void Motor::setDir(bool dir) {
	if (dirValue == dir)
		return;

	dirValue = dir;
	digitalWrite(dirPin, dirValue? HIGH: LOW);
}

float Motor::getSpeed() const
{
	return rotationSpeed;
}

bool Motor::isIdle()
{
	return isMotorIdle;
}

bool Motor::doPulse(unsigned long stepPeriodmicroSec) {
	unsigned long now = micros();
	if(now - lastHighTime > stepPeriodmicroSec){
		lastHighTime = now;
		pulseValue = true;
		PORTD |= (1 << this->pulsePin);
		return true;
	}
	else if ((now - lastHighTime) > (stepPeriodmicroSec / 2) && pulseValue) {
		pulseValue = false;
		PORTD &= ~(1 << this->pulsePin);
	}
	return false;
}

void Motor::disableMotor()
{
	if (isMotorIdle) {
		if (millis() - lastIdleTime > 2000) {
			digitalWrite(enablePin, HIGH);
		}
	}
	else {
		isMotorIdle = true;
		lastIdleTime = millis();
	}
}

void Motor::enableMotor() {
	isMotorIdle = false;
	digitalWrite(enablePin, LOW);
}

MotorSteps::MotorSteps(int pulsePin, int dirPin, int enablePin, float stepSize, float motorAngle): Motor(pulsePin, dirPin, enablePin, stepSize, motorAngle)
{
	steps_to_go = 0;
}

void MotorSteps::move(float angle)
{
	steps_to_go = (int)(angle / (motorAngle * stepSize));
}

void MotorSteps::loop()
{
	if (steps_to_go == 0) {
		disableMotor();
		return;
	}
	enableMotor();
	setDir(steps_to_go > 0);
	float speed = getSpeed();
	unsigned long stepPeriodmicroSec = (int)(1E6 / (speed * stepsPerRotation));
	if (doPulse(stepPeriodmicroSec)) {
		steps_to_go += -(steps_to_go / abs(steps_to_go));
	}
}
