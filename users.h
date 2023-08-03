#pragma once
#include <stdbool.h>
#include "utils.h"

#define USER_DB_FILE "./USERS.dat"

typedef unsigned long long very_long_int; // to use very_long_int for long integers
            // note: typedef is used to rename datatype


typedef struct User {
    char username[50];
    char password[50];
    char address[50];
    very_long_int account_number;
    float balance;
    Date birth_date;
    very_long_int phone_number;
    Date created_at;



} User;

User create_user(char *name, char *password, char *address, int birth_year,int birth_month,int birth_day,very_long_int phone_number);
         // declaring user structure that will return User 


// to print results, for my own ease
void print_user(User user);

// to save user to database
void save_user_to_database(User user);

// read users from database
User get_users_by_phone_number(very_long_int useraccount_to_find);

//get all users
User *get_all_users(int *num_users);

// delete account by taking account number as input
User delete_account_by_account_number(very_long_int account_number);

// update balance 
User update_balance(very_long_int account_number, float amount);

// sort users by aphabetical order of their username
void sort_users_by_username(User *users, int num_users);

//check validity of user
bool validate_user(very_long_int phone_number, const char *user_password);

