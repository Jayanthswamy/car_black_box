/*
 * File:   DS1307.c
 * Author: jayan
 *
 * Created on 26 December, 2024, 3:43 PM
 */

#include <xc.h>

#include "MAIN.h"
#include "i2c.h"
#include "DS1307.h"


/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

void init_DS1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_DS1307(SEC_ADDR);
	//set msb bit to turn off
	write_DS1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	dummy = read_DS1307(HOUR_ADDR);
	write_DS1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	write_DS1307(CNTL_ADDR, 0x93); 

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_DS1307(SEC_ADDR);
	//to turn on clear msb bit
	write_DS1307(SEC_ADDR, dummy & 0x7F); 

}

void write_DS1307(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
}

unsigned char read_DS1307(unsigned char address)
{
	unsigned char data;

	i2c_start();
	//writing function
	i2c_write(SLAVE_WRITE);
	//sending the reading address
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);//reading function
	data = i2c_read();//get the data from rtc
	i2c_stop();

	return data;
}
void get_time(void)
{
	clock_reg[0] = read_DS1307(HOUR_ADDR);
	clock_reg[1] = read_DS1307(MIN_ADDR);
	clock_reg[2] = read_DS1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void display_time(void)
{
	clcd_print(time, LINE2(0));
}

