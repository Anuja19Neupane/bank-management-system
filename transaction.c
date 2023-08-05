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

// // transaction read hunxa
// void readTransactionsFromFile()
// {
//     FILE *file = fopen("transactions.txt", "r");
//     if (file == NULL)
//     {
//         printf("No transaction found.\n");
//         return;
//     }

//     printf("Transactions:\n");
//     struct Transaction currentTransaction;
//     while (fscanf(file, "%llu %s %f %[^\n]", currentTransaction.account, currentTransaction.date, &currentTransaction.amount, currentTransaction.remarks) != EOF)
//     {
//         printf("Account: %s | Date: %s | Amount: %.2f | Description: %s\n",
//                currentTransaction.account, currentTransaction.date, currentTransaction.amount, currentTransaction.remarks);
//     }

//     fclose(file);
// }

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
     if (t.amount >= 0) {
        printf("Transaction Type: Deposit\n");
        printf("Amount: %.2f\n", t.amount);
    } else {
        printf("Transaction Type: Withdrawal\n");
        printf("Amount: %.2f\n", -t.amount); // Print the positive amount for withdrawal
    }
    printf("Remarks: %s\n", t.remarks);
    printf("Date: ");
    print_date(t.date);

    printf("Account number:%llu\n",t.account);
    printf("\n");

}


void print_transactions(Transaction *transactions, int size)
{
    for (int i = 0; i < size; i++)
    {
        print_transaction(transactions[i]);
        
    }
}

void getTransactionsForAccount(char *account)
{
    // Implementation without printf
}

void getTransactionsFromDate(char *date)
{
    // Implementation without printf
}
