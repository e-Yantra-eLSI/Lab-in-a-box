#ifndef F_CPU
#define F_CPU 16000000UL // set the CPU clock

#endif
#include <avr/io.h>		/* Include AVR std. library file */
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h> /* Include Delay header file */

int main(void)
{
	DDRJ = DDRJ | (1 << PJ4);
	DDRJ = DDRJ | (1 << PJ5);
	DDRJ = DDRJ | (1 << PJ6);
	DDRJ = DDRJ | (1 << PJ7);
	DDRH |= (1 << PH3); /* Make OC4A pin as output */
	TCNT4 = 0;			/* Set timer4 count zero */
	ICR4 = 2499;		/* Set TOP count for timer4 in ICR4 register */

	/* Set Fast PWM, TOP in ICR4, Clear OC4A on compare match, clk/64 */
	TCCR4A = (1 << WGM11) | (1 << COM1A1);
	TCCR4B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
	while (1)
	{
		OCR4A = 1234;
		PORTJ = PORTJ | (1 << PJ4);
		PORTJ = PORTJ & ~(1 << PJ5);
		_delay_ms(1000);
		OCR4A = 4321;
		PORTJ = PORTJ | (1 << PJ5);
		PORTJ = PORTJ & ~(1 << PJ4);
		_delay_ms(1000);
	}
}