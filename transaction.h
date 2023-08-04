#ifndef TRANSACTION_H
#define TRANSACTION_H

// # pragma once

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "transaction.h"

#define MAX_ACCOUNT_LEN 200
#define MAX_DATE_LEN 100
#define MAX_DESC_LEN 100

struct Transaction {
    char account[MAX_ACCOUNT_LEN];
    char date[MAX_DATE_LEN];
    double amount;
    char description[MAX_DESC_LEN];
};

void appendTransactionToFile(struct Transaction transaction);
void readTransactionsFromFile();

#endif

void createTransaction();
void listTransactions();
void getTransactionsForAccount(char *account);
void getTransactionsFromDate(char *date);

#endif
