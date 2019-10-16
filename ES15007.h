/* 
 * File:   ES15007.h
 * Author: raphael.pereira
 *
 * Created on 25 de Abril de 2019, 16:19
 */

#ifndef ES15007_H
#define	ES15007_H

#include <stdint.h>

#define ES15007_ADR 0x20
#define SERIAL_REG  0x01
#define STATUS_REG  0x03
#define PRESS_REG_L 0x16
#define PRESS_REG_H 0x17
#define TEMP_REG_L  0x18
#define TEMP_REG_H  0x19

//float pressure = 0;
//float temperature = 0;

uint16_t _serialnumber = 0;
//uint8_t  _status = 0;
uint16_t _pressure_lo = 0;
uint8_t _pressure_lo_LSB = 0;
uint8_t _pressure_lo_MSB = 0;
uint16_t _pressure_hi = 0;
uint8_t _pressure_hi_LSB = 0;
uint8_t _pressure_hi_MSB = 0;
uint16_t _temperature_lo = 0;
uint16_t _temperature_hi = 0;


uint16_t ES15007_Get_Serial();
uint8_t ES15007_Get_Status();
float ES15007_ReadPress();
float ES15007_ReadTemp();
float ES15007_ReadMeasure(uint8_t _register_l, uint8_t _register_h);

void ES15007_Init_Norm();


#endif	/* ES15007_H */

