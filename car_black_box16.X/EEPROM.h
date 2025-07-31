/* 
 * File:   EEPROM.h
 * Author: jayan
 *
 * Created on 24 December, 2024, 5:57 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H


#define SLAVE_READ_E   0XA1
#define SLAVE_WRITE_E  0XA0 


void write_external_eeprom(unsigned char address, unsigned char data);
unsigned char read_external_eeprom(unsigned char address);

#endif	/* EEPROM_H */

