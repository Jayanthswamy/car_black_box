/*
 * File:   view_log.c
 * Author: jayan
 *
 * Created on 26 December, 2024, 4:59 PM
 */

#include"xc.h"
#include"MAIN.h"
#include "EEPROM.h"


void view_log() {
    static unsigned char flag = 0, count = 0;
    //int k;
    if (flag == 0) {
        event_reader();
        flag = 1;
    }
    if (event_count == 0) {
        CLEAR_DISP_SCREEN;
        clcd_print("NO LOGS ", LINE1(0));
        clcd_print("TO DISPLAY", LINE2(0));
        __delay_ms(1000);
        CLEAR_DISP_SCREEN;
        flag = 0;
        count = 0;
        state = e_main_menu;
        return;
    }
    clcd_print("#  TIME    GR  SP", LINE1(0));
    events[count][0] = count + '0';
    clcd_print(events[count], LINE2(0));

    if (key == 1 && count < event_count - 1) {
        count++;
    } else if (key == 2 && count > 0) {
        count--;
    }

    if (key == 12) {
        
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
        //     read_addr = 0x00; 
        flag = 0;
        count = 0;
        return;
    }

}


