// the setup function runs once when you press reset or power the board
#include "Joystic.h"
#include "Motor.h"

float stepSize = 1.8f;
float motorAngle = 1 / 32.f;

Motor motor1(3, 2, 6, CONTINUOUS, stepSize, motorAngle);
Motor motor2(4, 5, 7, CONTINUOUS, stepSize, motorAngle);
Joystic joystic(A0, A1);

void setup() {
    // initialize digital pin 13 as an output.
    motor1.setup();
    motor2.setup();

    motor1.setSpeed(0.75f);
    motor2.setSpeed(0.75f);
    Serial.begin(9600);
}

int state_motor1 = 0;
int state_motor2 = 0;

unsigned long stopTime1 = 0;
unsigned long stopTime2 = 0;

// the loop function runs over and over again forever
void loop() {
    motor1.loop();
    motor2.loop();

    float x = joystic.getX();
    float y = joystic.getY();

    motor1.

}
