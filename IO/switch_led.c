#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock

#endif

#include <avr/io.h>     // Standard AVR IO Library
#include <util/delay.h> // Standard AVR Delay Library

int main(void)
{
    DDRC = DDRC | (1 << 0); // Makes PORTC1 as Output

    DDRE = DDRE & (~1 << 4); // Makes of PORTE4 as Input

    while (1) // infinite loop
    {

        if (bit_is_clear(PINE, 4)) // if switch is pressed
        {
            PORTC = PORTC & (~1 << 0); // HIGH ON PORTC0
        }
        else if (bit_is_set(PINE, 4)) // if switch is not pressed
        {
            PORTC = PORTC | (1 << 0); // LOW ON PORTC0
        }
    }
}
