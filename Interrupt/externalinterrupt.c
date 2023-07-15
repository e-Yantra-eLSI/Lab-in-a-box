#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock

#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// Function prototype for the interrupt service routine
ISR(INT0_vect);

int main(void)
{
  

    DDRD &= ~(1 << PD0);// Set PD2 (INT0 pin) as input
    DDRC = 0xFF; // port c set as output port
    // Enable external interrupt on falling edge of 
    PORTC=0;
    PORTD |= (1 << PD0);
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Enable INT0 external interrupt
    EIMSK |= (1 << INT0);

    // Enable global interrupts
    sei();

    while (1)
    {
        // Your main program logic here
    }

    return 0;
}

// Interrupt service routine for INT0
ISR(INT0_vect)
{
    // Interrupt handling code
    PORTC = ~PORTC; /* Toggle PORTC */
    _delay_ms(500);
}