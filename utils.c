
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

unsigned long long generate_random_10_digit_integer()
{
    unsigned long long result = 0;

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    // Generate the first 10 digits (each digit can be from 0 to 9)
    // rand() will generate random integers
    for (int i = 0; i < 10; i++)
    {
        result = result * 10 + rand() % 10; // rand() % 10 gives value between 0 to 9
    }
}

// create today date
Date get_current_date()
{

    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);

    //  current time lai local time ma convert garekoo
    localTime = localtime(&currentTime);

    // Extract year, month, and day from the local time
    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    Date d1 = {year, month, day};
    return d1;
}

// print date
void print_date(Date dt)
{
    printf("%d/%d/%d\n", dt.year, dt.month, dt.day);
}
void get_date(Date dt, char *date_string)
{
    sprintf(date_string, "%d/%d/%d ", dt.year, dt.month, dt.day);
}

void getInputString(char *input, int max_length)
{
    fgets(input, max_length, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline
}

void getInputDouble(double *input)
{
    char buffer[100]; // buffer size milauxa
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%lf", input);
}

int get_terminal_width()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;

    return terminalWidth;
}

int get_terminal_height()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_height = w.ws_row;

    return terminal_height;
}

void show_text(char *text, float fraction_x, float fraction_y)
{
    int terminal_width = get_terminal_width();
    int terminal_height = get_terminal_height();

    int xpos = (int)(fraction_x * terminal_width);
    int ypos = (int)(fraction_y * terminal_height);

   
    printf("\033[%d;%dH", ypos, xpos);

    printf("%s", text);
    printf(ANSI_RESET);

}

void printArbritaryPosition(char *text, float horizantal_fraction)

{

    // find out terminl's width

    int terminalWidth = get_terminal_width();
    int totalWidth = terminalWidth > 0 ? terminalWidth : 150; // Set a default value

    int padding = (int)(totalWidth * horizantal_fraction);
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }

    // Print the header text
    printf("%s", text);

    for (int i = padding + strlen(text); i < terminalWidth; i++)
    {
        printf(" ");
    }
}

void printTextAtCenter(char *text)
{

    // find out terminl's width
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;
    int totalWidth = terminalWidth > 0 ? terminalWidth : 150; // Set a default value

    // Calculate padding for horizontal centering
    int padding = (totalWidth - strlen(text)) / 2;

    // Print the header with proper formatting

    // Print left-side padding

    // printf("totalWidth: %d, padding: %d, strlen(text): %d\n", totalWidth, padding, strlen(text));
    // getchar();

    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }

    // Print the header text
    printf("%s", text);

    for (int i = padding + strlen(text); i < terminalWidth; i++)
    {
        printf(" ");
    }
    printf("\n");
}