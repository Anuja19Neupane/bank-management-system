#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for sleep () function
#include "users.h"
#include "utils.h"

User current_user;
char current_page[50];
int choice;
void main_page();// main_page function declaration
void login_page();// login_page function declaration
void create_account_page();
void profile_page();


// main_page function defination
void main_page()
{
    system("clear");
    printf("1. Log in\n");
    printf("2. Sign in\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    // printf("choice:%d\n",choice);

    // login_page
    if (choice==1)
    {
        // printf("choice:%d\n",choice);
        strcpy(current_page, "login_page");
        system("clear");  

        
    }
    // sign_in page
    else if (choice==2)
    {
        strcpy(current_page, "create_account_page");
    }
}
// login_page function defination
void login_page()
{
    
    very_long_int  your_phone_number;
    char your_password[50];

    printf("Login page\n");
    printf("Enter your phone number:\n");
    scanf("%llu",&your_phone_number);
    printf("Enter your password:\n");
    scanf("%s",your_password);
    while (getchar() != '\n'); 
    bool is_valid=validate_user(your_phone_number,your_password);
    if (is_valid)
    {
        printf("Login sucessful.\n");
        
        current_user=get_users_by_phone_number(your_phone_number);

        strcpy(current_page,"profile_page");
        // system("clear");
    }
    else
    {
        printf("invalid user.\n");
        getchar();
    }
    
    system("clear");
}
// create_account_page function defination
void create_account_page()
{
    char name[50];
    very_long_int phone_number;
    char address[50];
    int birth_year;
    int birth_month;
    int birth_day;
    char password[50];
    User user;

    system("clear");
    
    printf("Create user page\n");

   printf("Enter your full name: \n");
    scanf("%s", name);
    while (getchar() != '\n'); // Clear the input buffer after reading the string

    printf("Enter your phone number: \n");
    scanf("%llu", &phone_number);
    while (getchar() != '\n'); // Clear the input buffer after reading the number

    printf("Enter your address: \n");
    scanf("%s", address);
    while (getchar() != '\n'); // Clear the input buffer after reading the string 

   printf("Enter your birth year: \n");
    scanf("%d", &birth_year);
    while (getchar() != '\n'); // Clear the input buffer after reading the number

    printf("Enter your birth month: \n");
    scanf("%d", &birth_month);
    while (getchar() != '\n'); // Clear the input buffer after reading the number

    printf("Enter your birth day: \n");
    scanf("%d", &birth_day);
    while (getchar() != '\n'); // Clear the input buffer after reading the number

    printf("Enter your password: \n");
    scanf("%s", password);
    while (getchar() != '\n'); // Clear the input buffer after reading the string
    printf("User account sucessfully created.\n "); 
    sleep(2);
    
    // function call
    user= create_user(name,password,address,birth_year,birth_month,birth_day,phone_number);
    save_user_to_database(user);
    system("clear");
    strcpy(current_page, "login_page");
}



// profile_page function defination
void profile_page()
{
    char log_out;
    printf("Profile page\n");
    print_user(current_user);
    printf("Enter 'l' to logout.\n");
    scanf("%c",&log_out);

    if (log_out=='l')
    {
        strcpy(current_page,"login_page");

    }
    system("clear");



    }

    





int main()
{

    
    
    strcpy(current_page , "main_page");

    while (true)
    {
        
        
        if (strcmp(current_page, "main_page") == 0)
        {
            main_page(current_page); // function call

        }

        else if (strcmp(current_page, "create_account_page") == 0)
        {
            create_account_page();
        }

        else if (strcmp(current_page, "login_page") == 0)
        {
            login_page();
        }

        else if (strcmp(current_page, "profile_page") == 0)
        {
            profile_page();
        }

        
    }
}