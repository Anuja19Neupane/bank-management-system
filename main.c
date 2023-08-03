#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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
    bool is_valid=validate_user(your_phone_number,your_password);
    if (is_valid)
    {
        current_user=get_users_by_phone_number(your_phone_number);
        strcpy(current_page,"profile_page");
    }
    
    system("clear");
    
}

// create_account_page function defination
void create_account_page()
{
    printf("i am login page\n");
}

// profile_page function defination
void profile_page()
{
    printf("i am login page\n");
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