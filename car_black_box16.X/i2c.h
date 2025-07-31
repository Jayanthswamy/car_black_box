/* 
 * File:   i2c.h
 * Author: jayan
 *
 * Created on 26 December, 2024, 3:45 PM
 */

/* 
 * File:   i2c.h
 * Author: HP
 *
 * Created on 23 December, 2024, 5:56 PM
 */
#ifndef i2c_H
#define i2c_H


void init_i2c(void);
void i2c_start(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#endif