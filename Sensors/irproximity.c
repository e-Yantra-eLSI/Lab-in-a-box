#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock

#endif

#include <avr/io.h>     // Standard AVR IO Library
#include <util/delay.h> // Standard AVR Delay Library

int main(void)
{
    DDRH = DDRH | (1 << 2); // Makes pin 2 of PORTH as Output

    DDRA = DDRA & (~1 << 0); // Makes of pin 0 of PORTA as Input

    PORTA = PORTA | (1 << 0); // Makes pin 0 of PORTA as Pullup
    while (1)                 // infinite loop
    {

        if (bit_is_clear(PINA, 0)) // if obstacle is detected is pressed
        {
            PORTH = PORTH | (1 << 2); // HIGH ON PORTH PIN 2
        }
        else if (bit_is_set(PINA, 0)) // if obstacle is not detected
        {
            PORTH = PORTH & (~1 << 2); // LOW ON PORTH PIN 2
        }
    }
    return 0;
}