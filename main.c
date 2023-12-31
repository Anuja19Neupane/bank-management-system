#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>    // for sleep () function
#include <sys/ioctl.h> // for terminal width
#include "users.h"
#include "utils.h"
#include "transaction.h"

User current_user;
char current_page[50];
int choice;
void main_page();  // main_page function declaration
void login_page(); // login_page function declaration
void create_account_page();
void profile_page();
void deposit_page();
void withdraw_page();

 // main function
int main()
{

    strcpy(current_page, "main_page");
    system("clear"); //stdlib
    while (true)
    {
        printf(ANSI_BOLD ANSI_BG_BLUE ANSI_FG_WHITE);
        printTextAtCenter("");
        printTextAtCenter("Bank Management System");
        printTextAtCenter("");
        printf(ANSI_RESET "\n"); //escape code

        if (strcmp(current_page, "main_page") == 0)
        {
            printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
            show_text("Home Page\n", 0.45, 0.15);
            main_page(current_page); // function call
        }

        else if (strcmp(current_page, "create_account_page") == 0)
        {
            printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
            show_text("Sign Up Page\n", 0.45, 0.15);
            create_account_page(); // function call
        }

        else if (strcmp(current_page, "login_page") == 0)
        {
            printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
            show_text("Login Page\n", 0.45, 0.15);
            login_page(); //function call
        }

        else if (strcmp(current_page, "profile_page") == 0)
        {
            profile_page();//function call
        }

        else if (strcmp(current_page, "withdraw_page") == 0)
        {
            printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
            show_text("Withdraw Page\n", 0.45, 0.15);
            withdraw_page();
        }

        else if (strcmp(current_page, "deposit_page") == 0)
        {
            printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
            show_text("Deposit Page\n", 0.45, 0.15);
            deposit_page();
        }
    }
    return 0;
}

// main_page function defination
void main_page()
{
    // system("clear");
    // printf(ANSI_BG_GREEN ANSI_FG_WHITE ANSI_BOLD);
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_FG_WHITE);
    show_text("1. LOGIN\n", 0.4, 0.2);
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_FG_WHITE);
    show_text("2. CREATE ACCOUNT\n", 0.4, 0.3);
    // printf(ANSI_RESET);
    show_text("Enter your choice:", 0.35, 0.5);
    scanf("%d", &choice);
    system("clear");

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

    very_long_int phone_number;
    char password[50];

    show_text("Enter your phone number: ", 0.4, 0.2);
    scanf("%llu", &phone_number);
    clear_input_buffer();

    show_text("Enter your password: ", 0.4, 0.25);
    scanf("%s", password);
    clear_input_buffer();

    bool is_valid = validate_user(phone_number, password);
    if (is_valid)
    {
        printf("Login sucessful.\n");

        current_user = get_users_by_phone_number(phone_number);

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
    float vertical_line_gap = 0.05;
    char name[50];
    very_long_int phone_number;
    char address[50];
    int birth_year;
    int birth_month;
    int birth_day;
    char password[50];
    User user;

    show_text("Enter your name: ", 0.4, 0.2);
    scanf("%s", name);
    clear_input_buffer();

    show_text("Enter your phone number: ", 0.4, 0.2 + vertical_line_gap);
    scanf("%llu", &phone_number);
    clear_input_buffer();

    show_text("Enter your address: ", 0.4, 0.2 + 2 * vertical_line_gap);
    scanf("%s", address);
    clear_input_buffer();

    show_text("Enter your birth year: ", 0.4, 0.2 + 3 * vertical_line_gap);
    scanf("%d", &birth_year);
    clear_input_buffer();

    show_text("Enter your birth month: ", 0.4, 0.2 + 4 * vertical_line_gap);
    scanf("%d", &birth_month);
    clear_input_buffer();

    show_text("Enter your birth day: ", 0.4, 0.2 + 5 * vertical_line_gap);
    scanf("%d", &birth_day);
    clear_input_buffer();

    show_text("Enter your password: ", 0.4, 0.2 + 6 * vertical_line_gap);
    scanf("%s", password);
    clear_input_buffer();

    show_text("User account successfully created.\n", 0.4, 0.2 + 7 * vertical_line_gap);
    sleep(2);
    system("clear");

    user = create_user(name, password, address, birth_year, birth_month, birth_day, phone_number);
    save_user_to_database(user);
    strcpy(current_page, "login_page");
}

// deposit_page page
void deposit_page()
{

    very_long_int phone_number;
    float amount;
    char remarks[100];
    Transaction tran;

    show_text("Enter your phone number: ", 0.4, 0.2);

    scanf("%llu", &phone_number);
    clear_input_buffer();
        
    show_text("Enter amount to be deposited: ", 0.4, 0.25);
    scanf("%f", &amount);
    clear_input_buffer();
        

    show_text("Enter remarks: ", 0.4, 0.30);
    scanf("%s", remarks);
    clear_input_buffer();

    // function call to update the balance
    User updated_user = update_balance(phone_number, amount);

    // Check if the update was successful
    if (updated_user.account_number == 0)
    {
        printf("Error updating balance.\n");
    }
    else
    {
        createTransaction(amount, remarks, updated_user.account_number, &tran);
        current_user = updated_user;
        printf("Deposit successful. New balance: %.2f.  Press any key to continue....\n", updated_user.balance);

        getchar();
        strcpy(current_page, "profile_page");
        system("clear");
    }
}

// withdraw_page
void withdraw_page()
{
    very_long_int phone_number;
    char password[50];
    float amount;
    char remarks[100];
    Transaction tran;

    show_text("Enter your phone number: ", 0.4, 0.2);
    scanf("%llu", &phone_number);
    clear_input_buffer();

    show_text("Enter your password: ", 0.4, 0.25);
    scanf("%s", password);
     clear_input_buffer();

    // Check if the user with the given phone number and password exists
    bool is_valid_user = validate_user(phone_number, password);
    if (!is_valid_user)
    {
        printf("Invalid phone number or password.\n");
        return;
    }

    show_text("Withdraw amount: ", 0.4, 0.30);
    scanf("%f", &amount);
    clear_input_buffer();

    show_text("Enter remarks: ", 0.4, 0.4);
    scanf("%s", remarks);
    clear_input_buffer();

    // Check if the withdrawal amount is valid
    float account_balance = get_account_balance(phone_number);
    if (amount <= 0 || amount > account_balance)
    {
        printf("Invalid withdrawal amount.\n");
        getchar();
        system("clear");
        return;
    }
    printf("before update balance\n");
    // Perform the withdrawal (update balance and create transaction)
    User updated_user = update_balance(phone_number, -1 * amount);

    if (updated_user.account_number == 0)
    {
        printf("Error updating balance.\n");
    }
    else
    {
        // Create a transaction for the withdrawal
        createTransaction(-1 * amount, remarks, updated_user.account_number, &tran);

        printf("Withdrawal successful. New balance: %.2f . Press any key to continue....\n", updated_user.balance);
        getchar();
        current_user = updated_user;
        strcpy(current_page, "profile_page");
        system("clear");
    }
    system("clear");
}

// profile_page function defination
void profile_page()
{

    char log_out;
    Transaction transactions[100];
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
    printf("User Details:\n\n");
    printf(ANSI_RESET);
    show_user(current_user);

    // to display transaction details in profile page

    Transaction transactions_1[MAX_TRANSACTIONS]; // Assuming a maximum of 20 transactions

    int num_transactions = get_transactions_by_acc_number(current_user.account_number, transactions);

    // printf("\nTransaction History:\n");
    show_transactions(transactions, num_transactions, 5);

    // Print options for deposit or withdraw
    printf(ANSI_RESET);
    printf("\n");
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_FG_WHITE);
    show_text("1. Withdraw\n", 0.25, 0.75);
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_FG_WHITE);
    show_text("2. Deposit\n", 0.5, 0.75);
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_FG_WHITE);
    show_text("3. Logout\n", 0.75, 0.75);

    int wd_or_dp;
    show_text("Enter your choice:", 0.25, 0.8);
    scanf("%d", &wd_or_dp);
    clear_input_buffer();

    if (wd_or_dp == 1)
    {

        strcpy(current_page, "withdraw_page");
        system("clear");
    }
    else if (wd_or_dp == 2)
    {

        strcpy(current_page, "deposit_page");
        system("clear");
    }

    else if (wd_or_dp == 3)
    {

        strcpy(current_page, "login_page");
        system("clear");
    }
}
