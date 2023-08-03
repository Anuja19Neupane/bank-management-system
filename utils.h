#pragma once
typedef unsigned long long very_long_int; 

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
