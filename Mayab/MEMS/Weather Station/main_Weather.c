/*
 * File:   main_Weather.c
 * Author: xBug
 *
 * Created on October 10, 2018, 1:15 PM
 * 
 * Project Description:
 * Weather station that will take measurements every 10 seconds for 3 minutes
 * After the measurements have been done, the results will be displayed in 
 * a LCD screen.
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "LCD.h"
#include "DHT22.h"
#include "globalDefinitions.h"

const char takes = 18;
char data;
char level;

float temp;
float hum;
float psi;

unsigned char m[16];
unsigned char n[16];

void read_values(){
    get_dht_values();
    temp = temp + dht_temperature();
    hum = hum + dht_humidity();
}

void get_averages(){
    temp = temp/takes;
    hum = hum/takes;
    psi = psi/takes;
}
void print(int data){
    if(data == 0){
        LCD_Clear();
        sprintf(n, "%3.1f", temp);
        LCD_SetCursor(1,0);
        LCD_WriteString("Temperatura:");
        LCD_SetCursor(2,0);
        LCD_WriteString(n);
    } else if (data == 1){
        LCD_Clear();
        sprintf(n, "%3.1f", hum);
        LCD_SetCursor(1,0);
        LCD_WriteString("Humedad:");
        LCD_SetCursor(2,0);
        LCD_WriteString(n);
    } else if (data == 2){
        LCD_Clear();
        sprintf(n, "%3.1f", psi);
        LCD_SetCursor(1,0);
        LCD_WriteString("Presion:");
        LCD_SetCursor(2,0);
        LCD_WriteString(n);
    }
}

void loading(){
    sprintf(m, "Toma: %i / %i", level, takes);
    LCD_Clear();
    LCD_SetCursor(1,0);
    LCD_WriteString("Capturando datos");
    LCD_SetCursor(2,0);
    LCD_WriteString(m);
}

weather_init(){
    temp = 0;
    hum = 0;
    psi = 0;
}

void main() {
    
    // SETUP
    configPIC();
    LCD_Init();
    LCD_Clear();
    weather_init();
    
    // LOOP
    while(1){
        for(level = 1; level <= takes; level++){
            loading();
            read_values();
            wait_secs(10);
        }
        get_averages();
        for(int i = 0; i < 2; i++){
            print(i);
            wait_secs(5);
        }
        while(1){
            LCD_Clear();
            LCD_SetCursor(1,0);
            LCD_WriteString("Fin de la");
            LCD_SetCursor(2,0);
            LCD_WriteString("captura");
            while(1);
        }
    }
    return;
}