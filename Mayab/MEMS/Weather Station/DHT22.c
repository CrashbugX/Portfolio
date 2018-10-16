/*
 * File:   main_Weather.c
 * Author: xBug
 *
 * Created on October 10, 2018, 1:15 PM
 */
#include <pic18f4550.h>
#include <xc.h>
#include "globalDefinitions.h"
#include "config.h"

#define Data_Pin PORTAbits.RA2
#define Data_Pin_Direction TRISAbits.RA2

short Time_out = 0;
unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, Checksum ;
unsigned short Temp, RH;
float temperature, humidity;

void start_signal(){
  Data_Pin_Direction = OUTPUT;                      // Configure connection pin as output
  Data_Pin = 0;                                // Connection pin output low
  wait_ms(25);
  Data_Pin = 1;                                // Connection pin output high
  __delay_us(30);
  Data_Pin_Direction = INPUT;                      // Configure connection pin as input
}

short check_response(){
  __delay_us(40);
  if(!Data_Pin){                               // Read and test if connection pin is low
    __delay_us(80);
    if(Data_Pin){                              // Read and test if connection pin is high
        __delay_us(50);
        return 1;
        } else {
            return 0;
        }
    } else {
      return 0;
    }
}

unsigned char Read_Data(){
  unsigned char i, k, _data = 0;               // k is used to count 1 bit reading duration
  for(i = 0; i < 8; i++){
    k = 0;
    while(!Data_Pin){                          // Wait until pin goes high
      k++;
      if (k > 100) {Time_out = 1; break;}
      __delay_us(1);}
    __delay_us(30);
    if(!Data_Pin)
      bit_clear(_data, (7 - i));               // Clear bit (7 - i)
    else{
      bit_set(_data, (7 - i));                 // Set bit (7 - i)
      while(Data_Pin){                         // Wait until pin goes low
      k++;
      if (k > 100) {Time_out = 1; break;}
      __delay_us(1);}
    }
  }
  return _data;
}

void get_dht_values(){
    start_signal();
    if(check_response()){                     // If there is response from sensor
        RH_Byte1 = Read_Data();                 // read RH byte1
        RH_Byte2 = Read_Data();                 // read RH byte2
        T_Byte1 = Read_Data();                  // read T byte1
        T_Byte2 = Read_Data();                  // read T byte2
        Checksum = Read_Data();                 // read checksum
      
        if(Checksum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
            RH = RH_Byte1;
            RH = (RH << 8) | RH_Byte2;
            Temp = T_Byte1;
            Temp = (Temp << 8) | T_Byte2;
        }
    } else {
        RH_Byte1 = 101;                 // read RH byte1
        RH_Byte2 = 101;                 // read RH byte2
        T_Byte1 = 101;                  // read T byte1
        T_Byte2 = 101;
        Checksum = 101;
        Temp = 101;
        RH = 101;
    }
}


float dht_temperature(){
    temperature = (float)Temp/10;
    return temperature;
}

float dht_humidity(){
    humidity = (float)RH/10;
    return humidity;
}