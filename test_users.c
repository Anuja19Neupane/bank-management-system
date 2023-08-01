#include <stdio.h>
#include "users.h"
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
  // print_user(new_user);

  // save_user_to_database(new_user);

  // User db_user = get_users_by_account_number(123);
  // print_user(db_user);

  int num_users = 0;
  // getting all users
  
  User *all_users = get_all_users(&num_users);
  
  for (int i = 0; i < num_users; i++)
  {
    print_user(all_users[i]);
    
  }
  very_long_int dlt_this_acc;
  User dlt_acc = delete_account_by_account_number(894582764);
  all_users = get_all_users(&num_users);
  
  for (int i = 0; i < num_users; i++)
  {
    print_user(all_users[i]);
    
  }



  return 0;
}