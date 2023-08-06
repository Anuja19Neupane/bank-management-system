#pragma once
#include <sys/ioctl.h>
#include <unistd.h>


// ANSI color codes
#define ANSI_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_GREEN "\x1b[46m"
#define ANSI_FG_WHITE "\x1b[97m"
#define ANSI_BG_LIGHT_GRAY "\x1b[100m"
#define ANSI_BG_YELLOW "\033[43m"
#define ANSI_FG_RED "\x1b[31m"
#define ANSI_FG_GREEN "\x1b[32m"
#define ANSI_FG_YELLOW "\x1b[33m"
#define ANSI_FG_BLUE "\x1b[34m"
#define ANSI_FG_MAGENTA "\x1b[35m"
#define ANSI_FG_CYAN "\x1b[36m"
#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN "\x1b[46m"
#define ANSI_BG_WHITE "\x1b[47m"


typedef unsigned long long very_long_int; 

// structure for date
typedef struct Date
{
   int year;
   int month;
   int day;
}Date;


// to generate random integer for account number
very_long_int generate_random_10_digit_integer();


// create today date
Date get_current_date();

// print date
void print_date(Date dt);

void get_date(Date dt, char* date_string);

void getInputString(char *input, int max_length);
// void getInputDouble(double *input);


int get_terminal_width();
int get_terminal_height();

void show_text(char *text, float fraction_x, float fraction_y);