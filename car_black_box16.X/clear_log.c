/*
 * File:   clear_log.c
 * Author: jayan
 *
 * Created on 6 January, 2025, 10:58 PM
 */

#include"xc.h"
#include"MAIN.h"
#include "EEPROM.h"

void clear_log()
{
    event_count=0;
    write_addr = 0X00;
    clcd_print("Logs Cleared",LINE1(1));
    clcd_print("event_count=0",LINE2(1));
    __delay_ms(2000);
    state = e_main_menu;
    CLEAR_DISP_SCREEN;
    return;
    
}
