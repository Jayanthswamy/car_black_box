/*
 * File:   I2C.c
 * Author: jayan
 *
 * Created on 26 December, 2024, 3:46 PM
 */


#include "MAIN.h"
#include "DS1307.h"
#include "i2c.h"
#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
}

void i2c_idle(void)
{
	while (!SSPIF);
	SSPIF = 0;
}

void i2c_ack(void)
{
	//ACKSTAT is 1 slave not send ack
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void)
{
	SEN = 1;
	i2c_idle();
}

void i2c_stop(void)
{
	PEN = 1;
	i2c_idle();
}

void i2c_rep_start(void)
{
	RSEN = 1;
	i2c_idle();
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;
	i2c_idle();
}

void i2c_rx_mode(void)
{
	RCEN = 1;
	i2c_idle();
}

void i2c_no_ack(void)
{
	ACKDT = 1;
	ACKEN = 1;
}

unsigned char i2c_read(void)
{
	i2c_rx_mode();
	i2c_no_ack();

	return SSPBUF;
}