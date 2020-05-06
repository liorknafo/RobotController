// the setup function runs once when you press reset or power the board
#include "Joystic.h"
#include "Motor.h"

Motor motor1(2, 3, 6, STEPS);
Motor motor2(4, 5, 7, STEPS);
Joystic joystic(A0, A1);

void setup() {
    // initialize digital pin 13 as an output.
    motor1.setup();
    motor2.setup();

    motor1.setSpeed(0.75f);
    motor2.setSpeed(0.75f);
    Serial.begin(9600);
    //motor1.setRotation(135);
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
