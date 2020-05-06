// the setup function runs once when you press reset or power the board
#include "Joystic.h"
#include "Motor.h"

Motor motor1(3, 2, 6, STEPS, 1.8, 1 / 4.f);
Motor motor2(4, 5, 7, STEPS, 1.8, 1 / 4.f);
Joystic joystic(A0, A1);

void setup() {
    // initialize digital pin 13 as an output.
    motor1.setup();
    motor2.setup();

    motor1.setSpeed(0.5f);
    motor2.setSpeed(0.5f);
    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
    motor1.loop();
    motor2.loop();

    float x = joystic.getX();
    float y = joystic.getY();
    x = abs(x) < 0.1 ? 0 : x;
    y = abs(y) < 0.1 ? 0 : y;

    motor1.setRotation(x * 90);
    motor2.setRotation(y * 90);
}
