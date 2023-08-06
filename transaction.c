#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "utils.h"

char TRANSACTION_DB_FILE[50] = "./TRANSACTIONS.dat";

// transaction thapninxa
// void appendTransactionToFile(struct Transaction transaction)
// {
//     FILE *file = fopen("transactions.txt", "a");
//     if (file == NULL)
//     {
//         printf("No transaction found.\n");
//         return;
//     }

//     fprintf(file, "%llu %llu %.2f %s\n", transaction.account, transaction.date, transaction.amount, transaction.remarks);

//     fclose(file);
// }

// save transaction to db
int save_transaction_to_database(Transaction trans)
{

    FILE *fp;

    fp = fopen(TRANSACTION_DB_FILE, "ab");

    if (fp == NULL)
    {
        puts("Cannot open trasanction file.\n");

        return 0;
    }
    else
    {

        fwrite(&trans, sizeof(Transaction), 1, fp); // 1st argument is structure ko address
    }
    fclose(fp);
    return 1;
}

int get_transactions_by_acc_number(very_long_int acc_number, Transaction *transactions)
{
    Transaction t;
    FILE *fp;

    fp = fopen(TRANSACTION_DB_FILE, "rb");
    if (fp == NULL)
    {
        puts("Cannot read transaction file.\n");

        return 0;
    }
    int i = 0;
    // read struct from file one by one until user with given account is found
    // if user with account number not found return NULL
    while (fread(&t, sizeof(Transaction), 1, fp) == 1)

    // fread returns number of object it read
    // when 3rd argument is 1 , it should always return 1 cuz 3rd arguments specifies no of object we want
    // until it reach the EOF it returns 0
    {

        if (t.account == acc_number)

        {

            transactions[i] = t;
            i++;
        }
    }
    fclose(fp);
    return i;
}

// Function definitions without printf
int createTransaction(float amount, char *remarks, very_long_int account_number, Transaction *transaction)
{
    transaction->amount = amount; // arrow is used to access properties of struct using pointer to the structure
    transaction->account = account_number;
    strcpy(transaction->remarks, remarks);
    transaction->date = get_current_date();

    return save_transaction_to_database(*transaction);
}

// print transaction

void print_transaction(Transaction t)
{
    if (t.amount >= 0)
    {
        printf("Transaction Type: Deposit\n");
        printf("Amount: %.2f\n", t.amount);
    }
    else
    {
        printf("Transaction Type: Withdrawal\n");
        printf("Amount: %.2f\n", -t.amount); // Print the positive amount for withdrawal
    }
    printf("Remarks: %s\n", t.remarks);
    printf("Date: ");
    print_date(t.date);

    printf("Account number:%llu\n", t.account);
    printf("\n");
}

void print_transactions(Transaction *transactions, int size)
{
    for (int i = 0; i < size; i++)
    {
        print_transaction(transactions[i]);
    }
}

void show_transaction(Transaction t, int row_no, int vertical_offset)
{
    char date_str[15];
    get_date(t.date, date_str);

    int terminal_width = get_terminal_width();

    int isEvenRow = row_no % 2 == 0 ? 1 : 0;
    if (0)
    {
        printf(ANSI_BG_LIGHT_GRAY);
    }
    printf("\033[%d;%dH", row_no + vertical_offset, terminal_width / 2);
    printf("%-15s %-20s ", date_str, t.remarks);
    int width_covered = 15 + 20;

    if (t.amount >= 0)
    {
        printf(ANSI_FG_WHITE);
    }
    else
    {
        printf("\x1b[91m"); // ANSI color code for red
    }
    // 35 is width of date+discription
    printf("\033[%d;%dH", row_no + vertical_offset, terminal_width / 2 + width_covered);
    printf("%-15.2f", t.amount);
    printf(ANSI_RESET "\n");
}
void show_transactions(Transaction *transactions, int size, int vertical_offset)
{
    int terminal_width = get_terminal_width();
    printf(ANSI_BOLD ANSI_UNDERLINE ANSI_BG_GREEN ANSI_FG_WHITE);
    printf("\033[%d;%dH", vertical_offset, terminal_width / 2);

    printf("%-15s %-20s %-15s", "Date", "Description", "Amount");
    printf(ANSI_RESET "\n");

    for (int i = 0; i < size; i++)
    {
        show_transaction(transactions[i], i, vertical_offset + 1);
    }
}
