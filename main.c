/*
 * File:   main.c
 * Author: Raphael Pereira
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"
#include "my_delays.h"
#include "my_i2c.h"
#include "serial.h"
#include "ES15007.h"

void main(void)
{
    unsigned char aux[20];
    uint16_t serialn = 0;
    float temperaturee = 0;
    
    union 
   {
      uint16_t temperature_16;
      uint8_t temperature_databyte[2];
   }qzd_temp_lo;
   union 
   {
      uint16_t temperature_16;
      uint8_t temperature_databyte[2];
   }qzd_temp_hi;
    
    OSCCON = 0b01110010;

    ADCON1 = 0b00001111; // Set all pins in digital mode.
    CMCON = 0b00000111; // Disable all comparators.

    TRISA = 0b00000000; // Configure PORTA as output
    TRISB = 0b11111111;
    TRISC = 0b10111001;
    
    // Inicialize serial port
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    BAUDCON = 0b00001010;
    SPBRG = 16;  // 115200 @ 8MHz
    //SPBRG = 103; // 19200  @ 8MHz
    //SPBRG = 207; // 9600   @ 8MHz
    
    I2C_Close(); // Close the  I2C Bus.
    //I2C_Init(49); // I2C 100kHz, 20MHz-CRYSTAL.
    I2C_Init(19); // I2C 100kHz, 8MHz-CRYSTAL.
    //I2C_Init(9); // I2C 100kHz, 4MHz-CRYSTAL.
    
    //ES15007_Init_Norm();
    __delay_ms(50);
    
    putrsserial("OpenField sensor tester\n");
    putrsserial("PUC-Rio LSFO\n");
    
    while(1)
    {
        sprintf(aux, "Serial:      %6i\n", ES15007_Get_Serial());
        putrsserial(aux);
        sprintf(aux, "Status:      %4i\n", ES15007_Get_Status());
        putrsserial(aux);
        sprintf(aux, "Temperature: %010.5f °C\n", ES15007_ReadTemp());
        putrsserial(aux);
        sprintf(aux, "Pressure:    %010.5f Psi\n\n", ES15007_ReadPress());
        putrsserial(aux);
        Delay_ms(500);
    }
}