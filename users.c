#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include "users.h"
#include "utils.h"

User create_user(char *name, char *password, char *address, int birth_year, int birth_month, int birth_day, very_long_int phone_number)
{
    User u1;

    strcpy(u1.password, password);
    strcpy(u1.username, name);
    strcpy(u1.address, address);
    Date dob = {birth_year, birth_month, birth_day};
    u1.birth_date = dob;
    u1.phone_number = phone_number;
    u1.account_number = generate_random_10_digit_integer();
    u1.balance = 0; // initializing balance to be 0
    u1.created_at = get_current_date();
    return u1;
}

// everytime i want to check if my function is working properly or not,
// i have to type a long code to print the results, so creating function to print it will work
void print_user(User user)
{
    printf("Username: %s\n", user.username);
    printf("Password: %s\n", user.password);
    printf("Address: %s\n", user.address);
    printf("Account Number: %llu\n", user.account_number);
    printf("Balance: %.2f\n", user.balance);
    printf("Birth date: ");
    print_date(user.birth_date);
    printf("Created at: ");
    print_date(user.created_at);

    printf("Phone Number: %lld\n", user.phone_number);
    printf("\n\n");
}

// to save user to database
void save_user_to_database(User user)
{

    FILE *fp;

    fp = fopen(USER_DB_FILE, "a+");

    if (fp == NULL)
    {
        puts("Cannot open file.\n");
    }
    else
    {
        fwrite(&user, sizeof(User), 1, fp); // 1st argument is structure ko address
    }

    fclose(fp);
}

User get_users_by_phone_number(very_long_int useraccount_to_find)
{
    User user;
    FILE *fp;

    fp = fopen(USER_DB_FILE, "rb");
    if (fp == NULL)
    {
        puts("Cannot open file.\n");
    }
    // read struct from file one by one until user with given account is found
    // if user with account number not found return NULL
    while (fread(&user, sizeof(User), 1, fp) == 1)
    // fread returns number of object it read
    // when 3rd argument is 1 , it should always return 1 cuz 3rd arguments specifies no of object we want
    // until it reach the EOF it returns 0
    {
        if (user.phone_number == useraccount_to_find)
        {
            fclose(fp);
            return user;
        }
    }

    // User returntype vako le garda return NULL ; garna milena. so
    User empty_user;
    empty_user.phone_number = 0;
    fclose(fp);
    return empty_user;
}

// to get user
User *get_all_users(int *num_users_pointer)
{
    /*
    note: num_users is not input here, it is also output because we are not asking users to enter num_users
        instead we are calculating num_users for our own ease.

    */
    FILE *fp;
    User *users = 0; // initialize users to be 0

    fp = fopen(USER_DB_FILE, "rb");
    if (fp == NULL)
    {
        printf("Couldn't open file.\n");
    }

    // using fseek() and ftell() to know the size of the file
    fseek(fp, 0, SEEK_END); // this means end dekhi 0 uta samma gayera point gar
    long file_size = ftell(fp);
    // ftell() tells current position of the file pointer within the file
    *num_users_pointer = file_size / sizeof(User);

    fseek(fp, 0, SEEK_SET); // pointer lai feri suruma lagera xordiney

    // malloc for dynamic memory allocation
    //  malloc will only take certain memory according to our demand
    users = (User *)malloc(*num_users_pointer * sizeof(User)); // (User *) is typecast of malloc
    if (users == NULL)
    {
        fclose(fp);
        printf("There is an error with memory allocation.\n");
        return 0;
    }
    size_t read_users = fread(users, sizeof(User), *num_users_pointer, fp); // size_t will give size of object in bytes

    fclose(fp);
    // now compare the number of users to the users read
    if (read_users != *num_users_pointer)
    {
        free(users); // deallocating dynamically allocated memory
        // malloc use garera allocate garekoxa ,
        // jaba tesko kaam sakinxa we have to deallocate it otherwise it will result in memory leakage and memory becomes inaccessible

        users = NULL;
        // deallocate gareyapxi users lai NULL set garnu is good practise
        // to avoid accidental access to the freed memory.
        printf("Error in reading users from the file.\n");
        return 0;
    }

    return users;
}

// function to delete account

User delete_account_by_account_number(very_long_int account_number)
{
    /*
         user will definitely be returned , but if the account number provided by the user doesn't matches
         to any account number in the file it will show account number of returned user as 0.
     */
    User deleted_user;
    deleted_user.account_number = 0;
    User user;
    FILE *fp_in, *fp_out;

    fp_in = fopen(USER_DB_FILE, "rb");
    if (fp_in == NULL)
    {
        printf("Couldn't open file in.\n");
    }

    fp_out = fopen("temp.dat", "ab"); // create a temp.dat file to store temporary data
    //(except the accout_number and data are to be deleted.)
    if (fp_out == NULL)
    {
        printf("Couldn't open file out.\n");
    }
    while (fread(&user, sizeof(User), 1, fp_in) == 1)
    {
        if (account_number != user.account_number)
        {
            fwrite(&user, sizeof(User), 1, fp_out);
        }
        else
        {
            deleted_user = user;
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    remove("USERS.dat");
    rename("temp.dat", "USERS.dat");

    return deleted_user;
}

// update balance
User update_balance(very_long_int account_number, float amount)
{
    FILE *fp;
    User user;
    int found = 0;

    // Open the database file in read/write mode
    fp = fopen(USER_DB_FILE, "r+b");
    if (fp == NULL)
    {
        printf("Couldn't open the database file.\n");
        // Return an empty user to indicate failure
        User empty_user;
        empty_user.account_number = 0;
        return empty_user;
    }

    // Search for the user with the given account number
    while (fread(&user, sizeof(User), 1, fp) == 1)
    {
        if (user.account_number == account_number)
        {
            found = 1;
            // Update the balance
            user.balance += amount;
            // Move the file pointer back by the size of User to update the record in the file
            fseek(fp, -sizeof(User), SEEK_CUR);
            // Write the updated user back to the file
            fwrite(&user, sizeof(User), 1, fp);
            break; // No need to continue searching once found and updated
        }
    }

    fclose(fp);

    // Check if the user with the given account number was found or not
    if (!found)
    {
        printf("User with account number %llu not found.\n", account_number);
        // Return an empty user to indicate failure
        User empty_user;
        empty_user.account_number = 0;
        return empty_user;
    }

    // Return the updated user
    return user;
}

// sorting user by alphabetical order in username
void sort_users_by_username(User *users, int num_users)
{
    int i, j;
    User temp;

    // Bubble sort algorithm
    for (i = 0; i < num_users - 1; i++)
    {
        for (j = 0; j < num_users - i - 1; j++)
        {
            if (strcmp(users[j].username, users[j + 1].username) > 0)
            {
                // Swap the two users if they are in the wrong order
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

// Function to validate if the username exists in the list of users
bool validate_user(very_long_int phone_number, const char *user_password)
{
    int num_users = 0;
    User *all_users = get_all_users(&num_users);

    for (int i = 0; i < num_users; i++)
    {
        if (all_users[i].phone_number==phone_number && strcmp(all_users[i].password, user_password) == 0)
        {
            // User with the given username and password found, return true
            return true;
        }
    }

    // Username not found, return false
    return false;
}
