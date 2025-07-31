/*
 * File:   store_event.c
 * Author: jayan
 *
 * Created on 26 December, 2024, 4:55 PM
 */

//#include ""
#include"MAIN.h"
#include "EEPROM.h"

void event_store(unsigned char time[], unsigned char gear[], unsigned short speed)
{

    int j = 0;
    for (int i = 0; i < 12; i++) 
    {
        if (i < 8) 
        {
            if (i == 2 || i == 5) 
            {
                continue;
            }
            write_external_eeprom(write_addr, time[i]);
        }
        else if (i < 10) 
        {
            write_external_eeprom(write_addr, gear[j]);
            j++;

        }
        else if(i == 10)
        {



            write_external_eeprom(write_addr, ((speed / 10) + '0'));
             


        }
        else if (i ==11)
        {
         write_external_eeprom(write_addr, ((speed % 10) + '0'));   
        }
        write_addr++;

    }
    event_count++;

}
