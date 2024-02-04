#include <wiringPi.h>
#include <stdio.h>

#define BUTTON_PIN 17  // GPIO pin for the button
#define MIN_RPM 4000
#define MAX_RPM 8000
#define RPM_STEP 100

int rpm = MIN_RPM;

void buttonInterrupt() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        rpm += RPM_STEP;
        if (rpm > MAX_RPM) {
            rpm = MIN_RPM;
        }
        printf("RPM increased to %d\n", rpm);
        // Add code to control the RPM of your device using the updated value (rpm)
    }
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Error initializing WiringPi.\n");
        return 1;
    }

    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_DOWN);

    if (wiringPiISR(BUTTON_PIN, INT_EDGE_RISING, &buttonInterrupt) < 0) {
        printf("Error setting up ISR.\n");
        return 1;
    }

    printf("Press the button to increase RPM.\n");

    while (1) {
        // Your main program logic goes here
    }

    return 0;
}
