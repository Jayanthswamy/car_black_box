/*
 * File:   external EEPROM.c
 * Author: jayan
 *
 * Created on 24 December, 2024, 5:57 PM
 */


#include <xc.h>
#include "MAIN.h"
//#include "i2c.h"
void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i = 3000;i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	//writing function
	i2c_write(SLAVE_WRITE_E);
	//sending the reading address
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_E);//reading function
	data = i2c_read();//get the data from rtc
	i2c_stop();

	return data;
}