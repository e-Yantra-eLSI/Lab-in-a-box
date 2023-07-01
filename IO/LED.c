#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock
#endif
#include <avr/io.h>     // Standard AVR IO Library
#include <util/delay.h> // Standard AVR Delay Library

int main(void)
{
    DDRC = 0Xff; // PORTC as output
    while (1)
    {
        PORTC = 0xff;   // Turns ON All LEDs
        _delay_ms(500); // 500 milli second delay
        PORTC = 0x00;   // Turns OFF All LEDs
        _delay_ms(500); // 500 milli second delay
    }
}