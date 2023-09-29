#include  <lpc214x.h>

#define M1_MASK 0x00090000
#define M2_MASK 0x00060000

void  Delay(unsigned char j)
{  
    unsigned int  i;
    for(;j>0;j--)
    {
        for(i=0; i<60000; i++);
    }
}
                               
void M1_Forward()
{
    IO1CLR=M1_MASK;
    IO1SET=0x00080000;
}

void M1_Reverse()
{
    IO1CLR=M1_MASK;
    IO1SET=0x00010000;
}

void M1_Stop()
{
    IO1CLR=M1_MASK;
}

void M2_Forward()
{
    IO1CLR=M2_MASK;
    IO1SET=0x00040000;
}

void M2_Reverse()
{
    IO1CLR=M2_MASK;
    IO1SET=0x00020000;
}

void M2_Stop()
{
    IO1CLR=M2_MASK;
}

int main(void)
{
    PINSEL0 = 0x00000000;       // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
   
    IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);     // Set P1.16, P1.17, P1.18, P1.19 as Output
   
    while(1)    
    {
        M1_Forward();
        M2_Forward();
        Delay(100);
       
        M1_Stop();
        M2_Stop();
        Delay(100);
       
        M1_Reverse();
        M2_Reverse();
        Delay(100);
       
        M1_Stop();
        M2_Stop();
        Delay(100);
    }
}
