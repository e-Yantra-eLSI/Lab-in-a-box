
#include <lpc214x.h> //Includes LPC2148 register definitions
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define DATA_PORT() IO0SET = (1 << 16) // Function to select data port on LCD
#define READ_DATA() IO0SET = (1 << 17) // Function to select read operation on LCD
#define EN_HI() IO0SET = (1 << 18)     // Function to Enable LCD

#define COMMAND_PORT() IO0CLR = (1 << 16) // Function to select command port on LCD
#define WRITE_DATA() IO0CLR = (1 << 17)   // Function to select write operation on LCD
#define EN_LOW() IO0CLR = (1 << 18)       // Function to disable LCD

unsigned char String1[16] = {"   WELCOME TO   "};
unsigned char String2[16] = {"  LAB-IN A BOX!"};
int count = 0;
void delay_ms(uint16_t j) /* Function for delay in milliseconds  */
{
    uint16_t x, i;
    for (i = 0; i < j; i++)
    {
        for (x = 0; x < 6000; x++)
            ; /* loop to generate 1 milisecond delay with Pclk=15MHz */
    }
}

void Delay(unsigned char j)
{
    unsigned int i;
    for (; j > 0; j--)
    {
        for (i = 0; i < 60000; i++)
            ;
    }
}
__irq void EINT0_ISR(void)
{
    count++;
    IO0PIN = (IO0PIN ^ 0x00000100); /* Toggle LED */
    delay_ms(5);
    EXTINT = 0x01;
    VICVectAddr = 0x00000000;
}

void Delay_Small(unsigned char j)
{
    unsigned int i;
    for (; j > 0; j--)
    {
        for (i = 0; i < 1000; i++)
            ;
    }
}

unsigned char Busy_Wait() // This function checks the busy status of LCD
{
    unsigned int temp = 0;
    EN_LOW();
    COMMAND_PORT();
    READ_DATA();

    IO0PIN &= 0xFF87FFFF;
    IO0DIR &= 0xFF87FFFF;
    IO0PIN |= 0x00400000;

    do
    {
        EN_HI();
        EN_LOW();
        EN_HI();
        EN_LOW();
        temp = IO0PIN;
    } while ((temp & 0x00400000) == 0x00400000);
    EN_LOW();
    WRITE_DATA();
    IO0DIR &= 0xFF80FFFF;
    IO0DIR |= 0x007F0000;
    return (0);
}

void LCD_Command(unsigned int data) // This function is used to send LCD commands
{
    unsigned int temp = 0;
    EN_LOW();
    COMMAND_PORT();
    WRITE_DATA();

    temp = data;
    IO0PIN &= 0xFF87FFFF;
    IO0PIN |= (temp & 0xF0) << 15;

    EN_HI();
    EN_LOW();

    temp = data & 0x0F;
    IO0PIN &= 0xFF87FFFF;
    IO0PIN |= (temp) << 19;

    EN_HI();
    EN_LOW();
    while (Busy_Wait())
        ;
    Delay(10);
}

void LCD_Data(unsigned int data) // This function is used to send data to LCD
{
    unsigned int temp = 0;
    EN_LOW();
    DATA_PORT();
    WRITE_DATA();

    temp = data;
    IO0PIN &= 0xFF87FFFF;
    IO0PIN |= (temp & 0xF0) << 15;

    EN_HI();
    EN_LOW();

    temp = data & 0x0F;

    IO0PIN &= 0xFF87FFFF;
    IO0PIN |= (temp) << 19;

    EN_HI();
    EN_LOW();
    Delay_Small(1);
}

void LCD_Init()
{
    LCD_Command(0x20);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
}

void LCD_String(unsigned char *data)
{
    while (*data)
    {
        LCD_Data(*data);
        data++;
    }
}

int main(void)
{
    PINSEL0 = 0x00000000; // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    Delay(20);
    IO0DIR = (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16); // Set P0.16, P0.17, P0.18, P0.19, P0.20, P0.21, P0.22 as Output
    IO1DIR = (1 << 16);

    LCD_Init();
    LCD_Command(0x01);
    Delay(20);

    LCD_Command(0x80);
    // LCD_String(&String1[0]);
    LCD_Command(0xC0);
    // LCD_String(&String2[0]);
    VPBDIV = 0x00000002;
    EXTMODE = 0x01;                     /* Edge sensitive EINT0 */
    EXTPOLAR = 0x00;                    /* Falling sensitivity for EINT0 */
    EXTINT = 0x01;                      /* Clearing EINT0 flag */
    VICVectAddr0 = (unsigned)EINT0_ISR; /* EINT0 ISR Address */
    VICVectCntl0 = (0x00000020 | 14);   /* Enable EINT0 IRQ slot */
    VICIntEnable = 0x00004000;          /* Enable EINT0 interrupt */
    VICIntSelect = 0x00000000;          /* EINT0 configured as IRQ */
    PINSEL0 = 0x0000000C;               /* Configure P0.1 as EINT0 */
    IO0DIR = 0x00000100;                /* P0.8 as output to LED */
    LCD_Command(0x01);                  // Clear Display

    while (1)
    {
        char counter[16];
        LCD_Command(0x80);

        sprintf(counter, "Count: %d", count);
        LCD_String(&counter[0]);
        Delay(20);
    }
}
