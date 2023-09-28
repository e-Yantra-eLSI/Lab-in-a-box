#ifndef F_CPU

#define F_CPU 16000000UL // set the CPU clock
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 1 // Define the pin for the LED (PORTC.1)

void initExternalInterrupt() {
    EICRB |= (1 << ISC41); // Falling edge triggers the interrupt for INT4
    EIMSK |= (1 << INT4); // Enable external interrupt INT4
    sei(); // Enable global interrupts
}

void initLED() {
    DDRC |= (1 << LED_PIN); // Set LED pin as an output
}

int main(void) {
    initLED();
    initExternalInterrupt();

    while (1) {
        // Your main program logic here (if required)
    }
    return 0;
}

// External interrupt service routine for INT4
ISR(INT4_vect) {
    // Toggle the LED state
    PORTC ^= (1 << LED_PIN); // Toggle the LED at PORTC.1
}
