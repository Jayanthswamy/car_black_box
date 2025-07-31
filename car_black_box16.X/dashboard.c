#include <xc.h>
#include "MAIN.h"
//#include "clcd.h"

char *gear[] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C "};
unsigned short speed;
unsigned int gear_index = 0;
char *menu[4] = {"VIEW LOG           ", "CLEAR LOG         ", "DOWNLOAD LOG         ", "SET TIME         "};
static int menu_index = 0;
static int select_index = 1;

void view_dashboard() {
    display_time();
    speed = read_adc() / 10;
    if (speed < 100) {
        clcd_putch((speed / 10) + '0', LINE2(14));
        clcd_putch((speed % 10) + '0', LINE2(15));
    }
    if (key == MK_SW1) {
        if (gear_index == 8) 
        {
            gear_index = 1;
        } else if (gear_index < 7)
        {
            gear_index++;
            event_store(time, gear[gear_index], speed);

        } else if (gear_index > 7) 
        {
            gear_index = 7;
        }
    }
        else if (key == MK_SW2)
        {
            if (gear_index == 8)
            {
                gear_index = 1;
            }
            else if (gear_index > 1) 
            {
                gear_index--;
            event_store(time, gear[gear_index], speed);
        }
            else if(gear_index < 1)
            {
                gear_index = 1;
            }
        }
            else if (key == 3) {
            gear_index = 8;
            event_store(time, gear[gear_index], speed);
        }

        clcd_print("  TIME  GEAR  SD", LINE1(0));

        clcd_print(gear[gear_index], LINE2(10));

    }

void display_main_menu() {


    if (key == 2 && menu_index < 3) {
        menu_index++;

        if (select_index < 2) {

            select_index++;
            CLEAR_DISP_SCREEN;
        }
    } else if (key == 1 && menu_index > 0) {
        menu_index--;
        if (select_index > 1) {
            select_index--;
            CLEAR_DISP_SCREEN;
        }
    }
    if (select_index == 1) {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
        clcd_print(menu[menu_index], LINE1(3));
        clcd_print(menu[menu_index + 1], LINE2(3));
    } else {

        clcd_putch('*', LINE2(0));
        clcd_putch(' ', LINE1(0));

        clcd_print(menu[menu_index - 1], LINE1(3));
        clcd_print(menu[menu_index ], LINE2(3));
    }
    if (key == 11) {
        CLEAR_DISP_SCREEN;
        if (menu_index == 0) {
            state = e_view_log;
        }
        if (menu_index == 1) {
            state = e_clear_log;
        }
        if (menu_index == 2) {
            state = e_download_log;
        }
        if (menu_index == 3) {
            state = e_set_time;
        }
      
    }
}

void download_log() {

    event_reader();
    if (event_count == 0) {
        puts("NO LOGS TO DOWNLOAD\n\r");
        clcd_print("NO LOGS", LINE1(0));
        clcd_print("TO DOWNLOAD", LINE2(5));
        __delay_ms(1000);
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        return;
    }
    puts("#   TIME   GR SP");
    puts("\n\n\r");


    int s = 0;

    // puts("welcome\n\r");
    for (int i = 0; i < event_count; i++) {
        for (int j = 0; j < 16; j++) {
            if (j == 0) {
                putch(s + '0');
                s++;
            }
            putch(events[i][j]);

        }
        puts("\n\r");
    }
    if (event_count > 0) {
        clcd_print("DOWNLOADING..", LINE1(0));
        clcd_print("THROUGH UART", LINE2(2));
        __delay_ms(2000);

        state = e_main_menu;
        CLEAR_DISP_SCREEN;
        return;
    }
}

void set_time(void) {

    clcd_print("HH:MM:SS", LINE1(0));
    if (flag == 0) {
        hour = (time[0] - '0')*10 + (time[1] - '0');
        minute = (time[3] - '0')*10 + (time[4] - '0');
        second = (time[6] - '0')*10 + (time[7] - '0');
        flag = 1;
        field = 0;
    }
    
    static unsigned int wait = 0;
    if (key == 2) {
        field++;
        if (field > 2) {
            field = 0;
        }
        wait = 0;
    }
    if (field == 0) {
        if (key == 1) {
            hour++;
            if (hour > 23) {
                hour = 0;
            }
        }
        if (wait++ == 100) {
            clcd_putch((hour / 10) + '0', LINE2(0));
            clcd_putch((hour % 10) + '0', LINE2(1));
        } else if (wait >= 200) {
            clcd_print("  ", LINE2(0));
            wait = 0;
        }
        clcd_putch(':', LINE2(2));
        clcd_putch(':', LINE2(5));
        clcd_putch((minute / 10) + '0', LINE2(3));
        clcd_putch((minute % 10) + '0', LINE2(4));
        clcd_putch((second / 10) + '0', LINE2(6));
        clcd_putch((second % 10) + '0', LINE2(7));
        //            clcd_print("        ", LINE2(8));

    } else if (field == 1) {
        if (key == 1) {
            minute++;
            if (minute > 59)
                minute = 0;
        }
        if (wait++ == 100) {
            clcd_putch((minute / 10) + '0', LINE2(3));
            clcd_putch((minute % 10) + '0', LINE2(4));
        } else if (wait >= 200) {
            clcd_print("  ", LINE2(3));
            wait = 0;
        }
        clcd_putch(':', LINE2(2));
        clcd_putch(':', LINE2(5));
        clcd_putch((hour / 10) + '0', LINE2(0));
        clcd_putch((hour % 10) + '0', LINE2(1));
        clcd_putch((second / 10) + '0', LINE2(6));
        clcd_putch((second % 10) + '0', LINE2(7));
        //        clcd_print("        ", LINE2(8));
    } else if (field == 2) {
        if (key == 1) {
            second++;
            if (second > 59)
                second = 0;
        }
        if (wait++ == 100) {
            clcd_putch((second / 10) + '0', LINE2(6));
            clcd_putch((second % 10) + '0', LINE2(7));
        } else if (wait >= 200) {
            clcd_print("  ", LINE2(6));
            wait = 0;
        }
        clcd_putch(':', LINE2(2));
        clcd_putch(':', LINE2(5));
        clcd_putch((hour / 10) + '0', LINE2(0));
        clcd_putch((hour % 10) + '0', LINE2(1));
        clcd_putch((minute / 10) + '0', LINE2(3));
        clcd_putch((minute % 10) + '0', LINE2(4));
        //        clcd_print("        ", LINE2(8));
    }
     if(key == 11)
    {
        Jay =1;
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
    }
    if (Jay == 1) {
        unsigned char hr = ((hour / 10) << 4) | (hour % 10);
        unsigned char min = ((minute / 10) << 4) | (minute % 10);
        unsigned char sec = ((second / 10) << 4) | (second % 10);
        write_DS1307(HOUR_ADDR, hr);
        write_DS1307(MIN_ADDR, min);
        write_DS1307(SEC_ADDR, sec);
        state = e_dashboard;
        CLEAR_DISP_SCREEN;
        Jay = 0;
        flag = 0;
        return;
    }
   


}






