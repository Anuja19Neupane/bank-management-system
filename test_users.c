#include <stdio.h>
#include <stdbool.h>
#include "users.h"
#include "utils.h"
#define MAX_USERS 10000

int main()
{
  very_long_int random_number = generate_random_10_digit_integer();
  // printf("Random 10-digit integer: %llu\n", random_number);

  char name[] = "anuja";
  char password[] = "iampassword";
  char address[] = "itahari";
  int birth_year = 2005;
  int birth_month = 03;
  int birth_day = 19;
  long phone_number = 9829293245;

  User new_user = create_user(name, password, address, birth_year, birth_month, birth_day, phone_number);
  print_user(new_user);

  save_user_to_database(new_user);

  User db_user = get_users_by_account_number(123);
  if (db_user.account_number != 0)
  {
    print_user(db_user);
  }
  else
  {
    printf("User with account number not found\n");
  }

  int num_users = 0;
  // getting all users

  User *all_users = get_all_users(&num_users);

  for (int i = 0; i < num_users; i++)
  {
    print_user(all_users[i]);
    printf("-------------------------\n");
  }
  // very_long_int dlt_this_acc;
  // User dlt_acc = delete_account_by_account_number(894582764);
  // all_users = get_all_users(&num_users);

  // for (int i = 0; i < num_users; i++)
  // {
  //   print_user(all_users[i]);
  // }

  // update balance
  very_long_int account_number = 100;
  float amount = 1000.0;
  User updated_user = update_balance(account_number, amount);

  // Check if the update was successful
  if (updated_user.account_number != 0)
  {
    // Printing the updated user details
    printf("Updated User Details:\n");
    print_user(updated_user);
  }

  // Sort users by alphabetical order of username
  sort_users_by_username(all_users, num_users);

  // Print sorted users
  printf("sorted users\n");
  for (int i = 0; i < num_users; i++)
  {
    print_user(all_users[i]);
    printf("----------------------\n");
  }

  // check validity of user

  const char *username = "anuja";
  const char *user_password = "iampassword";

  bool is_valid = validate_user(username, user_password);

  if (is_valid)
  {
    printf("User exists.\n");
  }
  else
  {
    printf("User does not exist.\n");
  }

  // create today date
  Date today_date = get_current_date();
  print_date(today_date);

  return 0;
}
