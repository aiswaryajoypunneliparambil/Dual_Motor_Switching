

#include "LCD_8bit_file.h"


void LCD_Init()
{
    TRISB = 0;
    TRISD=0;
    MSdelay(5);
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
	LCD_Command(0x01);     /*clear display screen*/
	LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
	LCD_Command(0x0c);     /*display on cursor off*/
}


void LCD_Command(char cmd )
{
	ldata= cmd;            /*Send command to LCD */   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	MSdelay(1);
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char dat)
{
	ldata= dat;            /*Send command to LCD */  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	MSdelay(1);
	EN=0;
	MSdelay(3);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);



}
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }

