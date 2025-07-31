/*
 * File:   MAIN.c
 * Author: jayan
 *
 * Created on 12 December, 2024, 6:36 PM
 */

#include "MAIN.h"
#include "clcd.h"
State_t state;

void init_config()
{
    init_adc();
    init_matrix_keypad();
    init_clcd();
    init_i2c();
    init_DS1307();
    TRISB = 0X1E;
    
    state = e_dashboard;
//    state = e_main_menu;
}

void main(void) 
{
    init_config();

    while(1)
    {
        get_time();
        // Detect key press
        key=read_switches(1);
        switch (state)
        {
            case e_dashboard:
//                 Display dashboard
                view_dashboard();
                if(key == 11)
                {
                    state = e_main_menu;
                    CLEAR_DISP_SCREEN;
                }
                break;
            
            case e_main_menu:
                display_main_menu();
                // Display dashboard
                if(key == 12)
                {
                    state = e_dashboard;
                    CLEAR_DISP_SCREEN;
                }
                break;
            
            case e_view_log:
                // Display dashboard
                view_log();
                 if(key == 12)
                {
                    state = e_dashboard;
                    CLEAR_DISP_SCREEN;
                }
                break;
                 
            case e_download_log:
                download_log();
                 if(key == 12)
                {
                     CLEAR_DISP_SCREEN;
                    state = e_dashboard;
                    
                }
                break;
                
            case e_clear_log:
                clear_log();
                 if(key == 12)
                {
                    state = e_dashboard;
                    CLEAR_DISP_SCREEN;
                }
                break;
                
                      
            case e_set_time:
                set_time();
                break;
                
        }
        
    }
    
}
