/*
 * File:   event_reader.c
 * Author: jayan
 *
 * Created on 6 January, 2025, 10:57 PM
 */


#include"xc.h"
#include"MAIN.h"
#include "EEPROM.h"



void event_reader() {
    if (change == 0) {
        unsigned char read_addr = 0x00; //flag = 0,count = 0;
        // int k;
        //if (flag == 0) 
        //{
        for (int i = 0; i < event_count; i++) {
            events[i][0] = ' ';
            for (int j = 1; j < 16; j++) {
                if (j == 1 || j == 10 || j == 13) {
                    events[i][j] = ' ';
                   
                } else if (j == 4 || j == 7) {
                    
                    events[i][j] = ':';
                } else {

                    events[i][j] = read_external_eeprom(read_addr);
                    read_addr++;
                }
            }
            events[i][16] = '\0';

        }

    }
}
