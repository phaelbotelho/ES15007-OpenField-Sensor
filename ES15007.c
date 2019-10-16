/* 
 * File:   ES15007.c
 * Author: raphael.pereira
 *
 * Created on 25 de Abril de 2019, 16:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"
#include "ES15007.h"
#include "my_i2c.h"
#include "my_delays.h"


uint16_t ES15007_Get_Serial()
{
    union 
    {
       uint16_t serial_16;
       uint8_t serial_databyte[2];
    }serial;
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(SERIAL_REG);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    serial.serial_databyte[0] = I2C_ReadByte(1); // Read the data
    serial.serial_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    return serial.serial_16;
}

uint8_t ES15007_Get_Status()
{
    uint8_t status = 0;
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(STATUS_REG);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    status = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    return status;
}

float ES15007_ReadPress()
{
    float press = 0;
    union 
   {
      uint16_t pressure_16;
      uint8_t pressure_databyte[2];
   }qzd_press_lo;
   union 
   {
      uint16_t pressure_16;
      uint8_t pressure_databyte[2];
   }qzd_press_hi;
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(PRESS_REG_L);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    qzd_press_lo.pressure_databyte[0] = I2C_ReadByte(1); // Read the data
    qzd_press_lo.pressure_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(PRESS_REG_H);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    qzd_press_hi.pressure_databyte[0] = I2C_ReadByte(1); // Read the data
    qzd_press_hi.pressure_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    //press = ((qzd_press_lo.pressure_16 + 65536) * qzd_press_hi.pressure_16)/(65536);
    press = (float)(qzd_press_lo.pressure_16 + (65536 * qzd_press_hi.pressure_16))/(65536);
    
    return press;
}

float ES15007_ReadTemp()
{
    float temp = 0;
    
    union 
   {
      uint16_t temperature_16;
      uint8_t temperature_databyte[1];
   }qzd_temp_lo;
   union 
   {
      uint16_t temperature_16;
      uint8_t temperature_databyte[1];
   }qzd_temp_hi;
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(TEMP_REG_L);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    qzd_temp_lo.temperature_databyte[0] = I2C_ReadByte(1); // Read the data
    qzd_temp_lo.temperature_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(TEMP_REG_H);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    qzd_temp_hi.temperature_databyte[0] = I2C_ReadByte(1); // Read the data
    qzd_temp_hi.temperature_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    //temp = ((qzd_temp_lo.temperature_16 + 65536) * qzd_temp_hi.temperature_16)/(65536);
    temp = (float)(qzd_temp_lo.temperature_16 + (65536.0 * qzd_temp_hi.temperature_16))/(8388608.0);
    
    return temp;
}

float ES15007_ReadMeasure(uint8_t _register_l, uint8_t _register_h)
{
    float measure = 0;
    union 
   {
      uint16_t measure_16;
      uint8_t measure_databyte[2];
   }measure_lo;
   union 
   {
      uint16_t measure_16;
      uint8_t measure_databyte[2];
   }measure_hi;
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(_register_l);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    measure_lo.measure_databyte[0] = I2C_ReadByte(1); // Read the data
    measure_lo.measure_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    
    I2C_Start();
    I2C_WriteByte(ES15007_ADR);
    I2C_WriteByte(_register_h);
    I2C_RepeatedStart();
    I2C_WriteByte(ES15007_ADR + 1);
    measure_hi.measure_databyte[0] = I2C_ReadByte(1); // Read the data
    measure_hi.measure_databyte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    //press = ((qzd_press_lo.pressure_16 + 65536) * qzd_press_hi.pressure_16)/(65536);
    measure = (float)(measure_lo.measure_16 + (65536 * measure_hi.measure_16))/(65536);
    
    return measure;
}

void ES15007_Init_Norm()
{
    
}