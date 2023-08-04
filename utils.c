
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    //  current time lai local time ma convert gareko
    localTime = localtime(&currentTime);

    // Extract year, month, and day from the local time
    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    Date d1 = {year, month, day};
    return d1;
}


//print date 
void print_date(Date dt)
{
     printf("%d/%d/%d\n",dt.year,dt.month,dt.day);
}


void getInputString(char *input, int max_length) {
    fgets(input, max_length, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline
}

void getInputDouble(double *input) {
    char buffer[100]; // buffer size milauxa
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%lf", input);
}
