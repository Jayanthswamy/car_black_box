#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "i2c.h"
#include "DS1307.h"
#include "UART.h"
/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
          
} State_t;

unsigned char clock_reg[3];

unsigned char time[9];
unsigned event_count =0;
unsigned char events[10][11];
unsigned char minute=0;
unsigned char hour=0;
unsigned char second=0;
unsigned int field=0;
unsigned int Jay=0;
unsigned int change=0;
int flag = 0;
unsigned char write_addr = 0X00;



void get_time(void);
void display_time(void);

unsigned char key;
 State_t state; // App state

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(unsigned char time[], unsigned char gear[], unsigned short speed);
//Password function declaration
void password(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Change password function declaration
void change_password(void);

//Set time function declaration
void set_time(void);

//Download log function _decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);

#define SLAVE_READ_E	0xA1
#define SLAVE_WRITE_E		0xA0

//void event_store(unsigned char time[], unsigned char gear[], unsigned short speed);
//void view_log();
//void clear_log();
