#include "Initialiazation.h"

void ADC_Init();
int ADC_Read(int);
void switching1();
void switching2();

char data_R[10], data_L[10];    
int digital_R,digital_L,i=0,n=1000;  
float voltage_R, current_R, current_L, voltage_L,current_value_R,current_value_L, sum_R, sum_L;

#define vref 5.00               /*Reference Voltage is 5V*/

void main()
{  
    TRISD0 = 0;
    TRISD1 = 0;
    TRISC = 0;
    
 //   OSCCON=0x72;                /*Set internal Oscillator frequency to 8 MHz*/
    LCD_Init();                 /*Initialize 16x2 LCD*/
    ADC_Init();                 /*Initialize 10-bit ADC*/
    
 //   LATDbits.LD0 =1;
 //   LATDbits.LD1 =1;
    
    Data_read = EEPROM_Read(2);
    
    if(Data_read == 1){
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0; 
        EEPROM_Write(2,0);
    }else 
    {
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        EEPROM_Write(2,1);
    }
        
     
    
    LCD_String_xy(1,1,"Current is...");

    while(1)
    {  //   LCD_String_xy(2,1,"hiiii");  
        sum_R=0;
        sum_L=0;
        for(i = 0; i<n; i++) {
            
        digital_R = ADC_Read(0);
        voltage_R = digital_R*((float)vref/(float)1023);    /*Convert digital value into analog voltage*/
        current_R = (12*voltage_R)-29.214;
        sum_R = sum_R + current_R;
        
        digital_L = ADC_Read(1);
        voltage_L = digital_L*((float)vref/(float)1023);    /*Convert digital value into analog voltage*/
        current_L = (12*voltage_L)-29.265;
        sum_L = sum_L + current_L;
       
                            }
        
        current_value_R = sum_R/n;
        sprintf(data_R,"%.2f",current_value_R);                  /*It is used to convert integer value to ASCII string*/
//        strcat(data,"   A");                             /*Concatenate result and unit to print*/
        LCD_String_xy(2,1,data_R);                       /*send string data for printing*/  
        
        current_value_L = sum_L/n;
        sprintf(data_L,"%.2f",current_value_L);                  /*It is used to convert integer value to ASCII string*/
//        strcat(data,"   A");                             /*Concatenate result and unit to print*/
        LCD_String_xy(2,10,data_L);
//		MSdelay(500);
        
        if(Data_read == 1){
            switching1();
        }else
        {
            switching2();
        }
    }
    
}

void ADC_Init()
{    
    TRISA = 0xff;       /*set as input port*/
    ADCON1 = 0x0e;      /*ref vtg is VDD and Configure pin as analog pin*/    
    ADCON2 = 0x92;      /*Right Justified, 4Tad and Fosc/32. */
    ADRESH = 0;         /*Flush ADC output Register*/
    ADRESL = 0;   
}

int ADC_Read(int channel)
{
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);      /*channel 0 is selected i.e (CHS3CHS2CHS1CHS0=0000) 
                                                                      and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1<<ADON)|(1<<GO));                   /*Enable ADC and start conversion*/
    while(ADCON0bits.GO_nDONE==1);                  /*wait for End of conversion i.e. Go/done'=0 conversion completed*/        
    digital = (ADRESH*256) | (ADRESL);              /*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}

void switching1() {
//   PORTC = 0x0F;
    if(current_value_R > 1) {
//        PORTC = 0b00000011;
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 1;
//        for(i=0; i<n; i++);
     //   LATD1 = LATD1 || (1+LATD0);
        
    }
    else {
//        PORTC = 0b00000001;
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0;
    }
}

void switching2() {
//   PORTC = 0x0F;
    if(current_value_L > 1) {
//        PORTC = 0b00000011;
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 1;
//        for(i=0; i<n; i++);
     //   LATD1 = LATD1 || (1+LATD0);
        
    }
    else {
//        PORTC = 0b00000001;
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
    }
}


