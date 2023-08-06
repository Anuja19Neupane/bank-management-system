#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for sleep () function
#include "users.h"
#include "utils.h"
#include "transaction.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

// ANSI color codes
#define ANSI_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_FG_WHITE "\x1b[97m"
#define ANSI_BG_LIGHT_GRAY "\x1b[100m"

void printArbritaryPosition(char *text, float horizantal_fraction)

{

    // find out terminl's width
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;
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
    printf("\n");
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

User current_user;
char current_page[50];
int choice;
void main_page();  // main_page function declaration
void login_page(); // login_page function declaration
void create_account_page();
void profile_page();
void deposit_page();
void withdraw_page();

// main_page function defination
void main_page()
{
    // system("clear");
    printf(ANSI_BG_GREEN ANSI_FG_WHITE ANSI_BOLD);
    printArbritaryPosition("1. Log in", 0.5);
    
    printArbritaryPosition("2. Sign in", 0.5);
    printf(ANSI_RESET);
    printArbritaryPosition("Enter your choice: ", 0.5);
    scanf("%d", &choice);
    // printf("choice:%d\n",choice);

    if (choice == 1)
    {
        // printf("choice:%d\n",choice);
        strcpy(current_page, "login_page");
        system("clear");
    }

    else if (choice == 2)
    {
        strcpy(current_page, "create_account_page");
    }
}
// login_page function defination
void login_page()
{

    very_long_int your_phone_number;
    char your_password[50];

    printf("Login page\n");
    printf("Enter your phone number:\n");
    scanf("%llu", &your_phone_number);
    printf("Enter your password:\n");
    scanf("%s", your_password);
    while (getchar() != '\n')
        ;

    bool is_valid = validate_user(your_phone_number, your_password);
    if (is_valid)
    {
        printf("Login sucessful.\n");

        current_user = get_users_by_phone_number(your_phone_number);

        strcpy(current_page, "profile_page");
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
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the string

    printf("Enter your phone number: \n");
    scanf("%llu", &phone_number);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the number

    printf("Enter your address: \n");
    scanf("%s", address);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the string

    printf("Enter your birth year: \n");
    scanf("%d", &birth_year);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the number

    printf("Enter your birth month: \n");
    scanf("%d", &birth_month);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the number

    printf("Enter your birth day: \n");
    scanf("%d", &birth_day);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the number

    printf("Enter your password: \n");
    scanf("%s", password);
    while (getchar() != '\n')
        ;
    // Clear the input buffer after reading the string
    printf("User account sucessfully created.\n ");
    sleep(2);

    // function call
    user = create_user(name, password, address, birth_year, birth_month, birth_day, phone_number);
    save_user_to_database(user);
    system("clear");
    strcpy(current_page, "login_page");
}

// deposit_page page
void deposit_page()
{

    very_long_int your_phone_number;
    float amount;
    char remarks[100];
    Transaction tran;

    system("clear");
    printf("Deposit your amount.\n");
    printf("Enter your phone number: \n");
    scanf("%llu", &your_phone_number);
    while (getchar() != '\n')
        ;

    printf("Enter amount to be deposited: \n");
    scanf("%f", &amount);
    while (getchar() != '\n')
        ;

    printf("Enter remarks: \n");
    scanf("%s", remarks);
    while (getchar() != '\n')
        ;

    // function call to update the balance
    User updated_user = update_balance(your_phone_number, amount);

    // Check if the update was successful
    if (updated_user.account_number == 0)
    {
        printf("Error updating balance.\n");
    }
    else
    {
        createTransaction(amount, remarks, updated_user.account_number, &tran);
        current_user = updated_user;
        printf("Deposit successful. New balance: %.2f\n", updated_user.balance);
    }
}

// withdraw_page
void withdraw_page()
{
    very_long_int your_phone_number;
    char your_password[50];
    float amount;
    char remarks[100];
    Transaction tran;

    
    printf("Withdraw amount.\n");

    printf("Enter your phone number: \n");
    scanf("%llu", &your_phone_number);
    while (getchar() != '\n')
        ;

    printf("Enter your password: \n");
    scanf("%s", your_password);
    while (getchar() != '\n')
        ;

    // Check if the user with the given phone number and password exists
    bool is_valid_user = validate_user(your_phone_number, your_password);
    if (!is_valid_user)
    {
        printf("Invalid phone number or password.\n");
        return;
    }

    printf("Enter amount to withdraw: \n");
    scanf("%f", &amount);
    while (getchar() != '\n')
        ;

    printf("Enter remarks: \n");
    fgets(remarks, sizeof(remarks), stdin);
    remarks[strcspn(remarks, "\n")] = '\0'; // Remove the newline character

    // Check if the withdrawal amount is valid
    float account_balance = get_account_balance(your_phone_number);
    if (amount <= 0 || amount > account_balance)
    {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    // Perform the withdrawal (update balance and create transaction)
    User updated_user = update_balance(your_phone_number, -amount);

    if (updated_user.account_number == 0)
    {
        printf("Error updating balance.\n");
    }
    else
    {
        // Create a transaction for the withdrawal
        createTransaction(-amount, remarks, updated_user.account_number, &tran);

        printf("Withdrawal successful. New balance: %.2f\n", updated_user.balance);
    }
    system("clear");
}

// profile_page function defination
void profile_page()
{

    char log_out;
    Transaction transactions[100];
    
    printf("Profile page\n");

    printf("User Details:\n");
    print_user(current_user);

    // to display transaction details in profile page

    Transaction transactions_1[MAX_TRANSACTIONS]; // Assuming a maximum of 20 transactions

    int num_transactions = get_transactions_by_acc_number(current_user.account_number, transactions);

    printf("\nTransaction History:\n");
    print_transactions(transactions, num_transactions);

    // Print options for deposit or withdraw
    printf("\n1. Withdraw\n");
    printf("2. Deposit\n");

    int wd_or_dp;
    printf("Enter your choice: ");
    scanf("%d", &wd_or_dp);
    while (getchar() != '\n')
        ;
    system("clear");
    if (wd_or_dp == 1)
    {

        strcpy(current_page, "withdraw_page");
        withdraw_page();
    }
    else if (wd_or_dp == 2)
    {

        strcpy(current_page, "deposit_page");
        deposit_page();
    }
    

    printf("Enter 'l' to logout.\n");
    scanf("%c", &log_out);
    while (getchar() != '\n')
        ;

    if (log_out == 'l')
    {
        strcpy(current_page, "login_page");
    }
    system("clear");
}

int main()
{

    strcpy(current_page, "main_page");

    while (true)
    {
        printf(ANSI_BOLD ANSI_BG_BLUE ANSI_FG_WHITE);
        printTextAtCenter("");
        printTextAtCenter("Bank Management System");
        printTextAtCenter("");
        printf(ANSI_RESET "\n");

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