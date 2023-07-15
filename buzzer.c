
#include <lpc214x.h>
#include <stdint.h>
#define buzzer (1 << 11) // P0.11
void Delay(unsigned int);
int main(void)
{
	PINSEL0 = 0x00000000; // P0.0 to P0.15 GPIO

	IO0DIR = buzzer; // P0.11 as output
	while (1)

	{
		IO0SET = buzzer; // P0.11 high
		Delay(500);		 // 500 ms delay
		IO0CLR = buzzer; // P0.11 low
		Delay(500);		 // 500 ms delay
	}
}
void Delay(unsigned int ms) // delay routine
{
	unsigned int i, j;
	for (j = 0; j < (ms / 10); j++)
	{
		for (i = 0; i < 60000; i++)
			;
	}
}
