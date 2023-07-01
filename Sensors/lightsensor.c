#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock

#endif

#include <avr/io.h>     // Standard AVR IO Library
#include <util/delay.h> // Standard AVR Delay Library

int main(void)
{
    DDRC = DDRC | (1 << 0); // Makes PORTC0 as Output

    DDRA = DDRA & (~1 << 0); // Makes of PORTA0 as Input

    while (1) // infinite loop
    {

        if (bit_is_clear(PINA, 0)) // certain amount of light is detected
        {
            PORTC = PORTC | (1 << 0); // LOW ON PORTC0
        }
        else if (bit_is_set(PINA, 0)) // certain amount of light is not detected
        {
            PORTC = PORTC & (~1 << 0); // HIGH ON PORTC0
        }
    }
    return 0;
}