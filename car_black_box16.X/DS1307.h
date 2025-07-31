/* 
 * File:   DS1307.h
 * Author: jayan
 *
 * Created on 26 December, 2024, 3:43 PM
 */

#ifndef DS1307_H
#define DS1307_H

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0


#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07


void write_DS1307(unsigned char address1,  unsigned char data);
unsigned char read_DS1307(unsigned char address1);
void init_DS1307(void);
#endif