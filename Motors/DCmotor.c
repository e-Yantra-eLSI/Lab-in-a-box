#include <lpc214x.h>

#define RUN 1
#define STOP 0

#define FORWARD 1
#define REVERSE 0

#define SW1 (IO0PIN & 0x00008000) // Macro Functions to read Push button switches on LPC2148 dev. board
#define SW2 (IO0PIN & 0x00002000)
#define SW3 (IO0PIN & 0x00001000)
#define SW4 (IO0PIN & 0x40000000)

#define M1_MASK 0x00090000
#define M2_MASK 0x00060000

void Delay(unsigned char j)
{
    unsigned int i;
    for (; j > 0; j--)
    {
        for (i = 0; i < 60000; i++)
            ;
    }
}

void M1_Forward()
{
    IO1CLR = M1_MASK;
    IO1SET = 0x00080000;
}

void M1_Reverse()
{
    IO1CLR = M1_MASK;
    IO1SET = 0x00010000;
}

void M1_Stop()
{
    IO1CLR = M1_MASK;
}

void M2_Forward()
{
    IO1CLR = M2_MASK;
    IO1SET = 0x00040000;
}

void M2_Reverse()
{
    IO1CLR = M2_MASK;
    IO1SET = 0x00020000;
}

void M2_Stop()
{
    IO1CLR = M2_MASK;
}

int main(void)
{
    unsigned char M1_Status = 0;
    unsigned char M2_Status = 0;
    unsigned char M1_DIR = 0;
    unsigned char M2_DIR = 0;

    PINSEL0 = 0x00000000; // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    IO1DIR = (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16); // Set P1.16, P1.17, P1.18, P1.19 as Output
    IO0DIR = (0 << 12) | (0 << 13) | (0 << 15) | (0 << 30); // Set P0.12, P0.13, P0.15, P0.30 as Input to read switch status

    while (1)
    {
        if (!SW1)
        {
            if (M2_Status == STOP)
            {
                M2_Status = RUN;
            }
            else
            {
                M2_Status = STOP;
            }
        }

        if (!SW3)
        {
            if (M1_Status == STOP)
            {
                M1_Status = RUN;
            }
            else
            {
                M1_Status = STOP;
            }
        }

        if (!SW2)
        {
            if (M2_DIR == REVERSE)
            {
                M2_DIR = FORWARD;
            }
            else
            {
                M2_DIR = REVERSE;
            }
        }

        if (!SW4)
        {
            if (M1_DIR == REVERSE)
            {
                M1_DIR = FORWARD;
            }
            else
            {
                M1_DIR = REVERSE;
            }
        }

        if (M1_Status == STOP)
        {
            M1_Stop();
        }
        else if (M1_DIR == FORWARD)
        {
            M1_Forward();
        }
        else if (M1_DIR == REVERSE)
        {
            M1_Reverse();
        }

        if (M2_Status == STOP)
        {
            M2_Stop();
        }
        else if (M2_DIR == FORWARD)
        {
            M2_Forward();
        }
        else if (M2_DIR == REVERSE)
        {
            M2_Reverse();
        }

        Delay(50);
    }
    return (0);
}