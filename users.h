#pragma once

#define USER_DB_FILE "./USERS.dat"

typedef unsigned long long very_long_int; // to use very_long_int for long integers
            // note: typedef is used to rename datatype

typedef struct User {
    char username[50];
    char password[50];
    char address[50];
    very_long_int account_number;
    float balance;
    int birth_year;
    int birth_month;
    int birth_day;
    very_long_int phone_number;

    
} User;

User create_user(char *name, char *password, char *address, int birth_year,int birth_month,int birth_day,very_long_int phone_number);
         // declaring user structure that will return User 

// to generate random integer for account number
very_long_int generate_random_10_digit_integer();

// to print results, for my own ease
void print_user(User user);

// to save user to database
void save_user_to_database(User user);

// read users from database
User get_users_by_account_number(very_long_int useraccount_to_find);

//get all users
User *get_all_users(int *num_users);

// delete account by taking account number as input
User delete_account_by_account_number(very_long_int account_number);