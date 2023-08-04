#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"

// transaction thapninxa
void appendTransactionToFile(struct Transaction transaction)
{
    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL)
    {
        printf("No transaction found.\n");
        return;
    }

    fprintf(file, "%s %s %.2f %s\n", transaction.account, transaction.date, transaction.amount, transaction.description);

    fclose(file);
}

// transaction read hunxa
void readTransactionsFromFile()
{
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL)
    {
        printf("No transaction found.\n");
        return;
    }

    printf("Transactions:\n");
    struct Transaction currentTransaction;
    while (fscanf(file, "%s %s %lf %[^\n]", currentTransaction.account, currentTransaction.date, &currentTransaction.amount, currentTransaction.description) != EOF)
    {
        printf("Account: %s | Date: %s | Amount: %.2f | Description: %s\n",
               currentTransaction.account, currentTransaction.date, currentTransaction.amount, currentTransaction.description);
    }

    fclose(file);
}

// Function definitions without printf
void createTransaction()
{
    // Implementation without printf
}

void listTransactions()
{
    // Implementation without printf
}

void getTransactionsForAccount(char *account)
{
    // Implementation without printf
}

void getTransactionsFromDate(char *date)
{
    // Implementation without printf
}
