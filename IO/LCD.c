
#include  <lpc214x.h>	  //Includes LPC2148 register definitions

#define DATA_PORT() IO0SET=(1<<16)		 //Function to select data port on LCD
#define READ_DATA() IO0SET=(1<<17)		 //Function to select read operation on LCD
#define EN_HI() IO0SET=(1<<18)			 //Function to Enable LCD


#define COMMAND_PORT() IO0CLR=(1<<16)	  //Function to select command port on LCD
#define WRITE_DATA() IO0CLR=(1<<17)		  //Function to select write operation on LCD
#define EN_LOW() IO0CLR=(1<<18)			  //Function to disable LCD

unsigned char String1[16]={"   WELCOME TO   "};
unsigned char String2[16]={"  LAB-IN A BOX!"};

void Delay(unsigned char j)
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}

void Delay_Small(unsigned char j)
{
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<1000; i++);
 } 
}
                               

unsigned char Busy_Wait()			   //This function checks the busy status of LCD
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 READ_DATA();
 
 IO0PIN&=0xFF87FFFF;	  
 IO0DIR&=0xFF87FFFF;
 IO0PIN|=0x00400000;
 
 do{
 EN_HI();
 EN_LOW();
 EN_HI();
 EN_LOW();
 temp=IO0PIN;
 }
 while((temp & 0x00400000)==0x00400000);
 EN_LOW();
 WRITE_DATA();
 IO0DIR&=0xFF80FFFF;
 IO0DIR|=0x007F0000;
 return (0);
}    


void LCD_Command(unsigned int data)			  //This function is used to send LCD commands
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 while(Busy_Wait());
 Delay(10);
} 


void LCD_Data(unsigned int data)		   //This function is used to send data to LCD
{
 unsigned int temp=0;
 EN_LOW();
 DATA_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

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
 while(*data)
 {
  LCD_Data(*data);
  data++;
 } 
}  


int main(void)
{ 
 PINSEL0 = 0x00000000;		// Enable GPIO on all pins
 PINSEL1 = 0x00000000;
 PINSEL2 = 0x00000000;

 Delay(20);
 IO0DIR = (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17) | (1<<16);		// Set P0.16, P0.17, P0.18, P0.19, P0.20, P0.21, P0.22 as Output
 IO1DIR = (1<<16);
 
 LCD_Init();
 LCD_Command(0x01);
 Delay(20);

 LCD_Command(0x80);
 LCD_String(&String1[0]);
 LCD_Command(0xC0);
 LCD_String(&String2[0]);
 while(1)	
 { 
  
   
 }
 
}

