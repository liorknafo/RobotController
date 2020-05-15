// 
// 
// 

#include "Motor.h"

Motor::Motor(int pulsePin, int dirPin, int enablePin, MotorMode motorMode, float stepSize, float motorAngle) :
	stepsPerRotation((360.00 / stepSize) / motorAngle), stepSize(stepSize), motorAngle(motorAngle), motorMode(motorMode) {
	this->pulsePin = pulsePin;
	this->dirPin = dirPin;
	this->enablePin = enablePin;
	
	this->rotation = 0;
	this->desiredRotation = 0;
	this->rotationSpeed = 0;
	this->dirValue = true;
	
	this->lastIdleTime = 0;
	this->lastHighTime = 0;
	this->pulseValue = false;
}

void Motor::setSpeed(float rotationSpeed) {
	this->rotationSpeed = rotationSpeed;
}

float Motor::normalize_angle(float angle) const {
	if (angle > 360) {
		return angle - 360;
	}
	if (angle < 0) {
		return 360 + angle;
	}
	return angle;
}

void Motor::setRotation(float desiredRotation) {
	this->desiredRotation = normalize_angle(desiredRotation);
}

void Motor::setup() {
	pinMode(pulsePin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enablePin, OUTPUT);
}

bool Motor::calcDirection() const {
	float x_desired = cos(desiredRotation * PI / 180.f);
	float y_desired = sin(desiredRotation * PI / 180.f);
	float x_now = cos(rotation * PI / 180.f);
	float y_now = sin(rotation * PI / 180.f);

	float dirPin = x_desired * y_now - x_now * y_desired;
	return dirPin > 0;
}

void Motor::loop() {
	switch (motorMode) {
	case CONTINUOUS:
		doContinuous();
		break;
	case STEPS:
		doSteps();
		break;
	}
}

void Motor::setDir(bool reverse) {
	if (dirValue == reverse)
		return;
	dirValue = reverse;
	if (reverse) {
		digitalWrite(dirPin, LOW);
	}
	else {
		digitalWrite(dirPin, HIGH);
	}
	delay(100);
}

float Motor::getRotation() const
{
	return rotation;
}

float Motor::getSpeed() const
{
	return rotationSpeed;
}

bool Motor::isIdle()
{
	return isMotorIdle;
}

float Motor::calcAngleDis(float angle1, float angle2) const {
	float delta = angle1 - angle2;
	delta = abs(delta);
	if (delta > 180.f)
	{
		return 360.f - delta;
	}
	return delta;
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

void Motor::doSteps() {
	if (calcAngleDis(desiredRotation, rotation) < stepSize * motorAngle)
	{
		//desiredRotation = rotation;
		disableMotor();
		return;
	}
	if (rotationSpeed == 0)
	{
		disableMotor();
		return;
	}
	if (isMotorIdle) {
		if (calcAngleDis(desiredRotation, rotation) < stepSize * motorAngle * 10) {
			disableMotor();
			return;
		}
	}
	enableMotor();
	
	bool dir = calcDirection();
	setDir(dir);

	unsigned long stepPeriodmicroSec = 10000;// (1E6 / (rotationSpeed * stepsPerRotation));
	if (doPulse(stepPeriodmicroSec)) {
		rotation += (dir ? -1 : 1) * stepSize * motorAngle;
		rotation = normalize_angle(rotation);
	}
}

void Motor::doContinuous() {
	if (rotationSpeed == 0) {
		disableMotor();
		return;
	}
	enableMotor();

	unsigned long stepPeriodmicroSec = (1E6 / (rotationSpeed * stepsPerRotation * 2.f)) - 5;
	PORTD |= (1 << this->pulsePin);
	delayMicroseconds(stepPeriodmicroSec);
	PORTD &= ~(1 << this->pulsePin);
	delayMicroseconds(stepPeriodmicroSec);
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