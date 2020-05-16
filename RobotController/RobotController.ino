// the setup function runs once when you press reset or power the board
#include "Joystic.h"
#include "Motor.h"

float stepSize = 1.8f;
float motorAngle = 1 / 32.f;

MotorSteps motor1(3, 2, 6, stepSize, motorAngle);
MotorSteps motor2(4, 5, 7, stepSize, motorAngle);
Joystic joystic(A0, A1);

void setup() {
    // initialize digital pin 13 as an output.
    motor1.setup();
    motor2.setup();

    motor1.setSpeed(0.25f);
    motor2.setSpeed(0.25f);
    Serial.begin(9600);
}

float calc_dir(float jInput) {
    if (abs(jInput) < 0.1)
        return 0;
    return jInput / abs(jInput);
}

void handle_motor(float jInput, MotorSteps& motor) {
    float dir = calc_dir(jInput);
    
    if (dir == 0) {
        motor.move(0);
        return;
    }
    motor.move(20 * dir);
}

unsigned long lastCheck = 1;
// the loop function runs over and over again forever
void loop() {
    motor1.loop();
    motor2.loop();

    if (millis() - lastCheck > 100) {
        lastCheck = millis();
        float x = joystic.getX();
        float y = joystic.getY();
        handle_motor(x, motor1);
        handle_motor(y, motor2);
    }
}
