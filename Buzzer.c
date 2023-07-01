#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock
#endif
#include <avr/io.h>     // Standard AVR IO Library
#include <util/delay.h> // Standard AVR Delay Library

int main(void)
{
    DDRH = 0XFF; // Initialize buzzer pin PH2 as output
    while (1)
    {
        PORTH = 0x00;    // Turn ON the buzzer
        _delay_ms(1000); // 1 second delay
        PORTH = 0xFF;    // Turn OFF the buzzer
        _delay_ms(1000); // 1 second delay
    }
}
