#ifndef TRANSACTION_H
#define TRANSACTION_H


#include "transaction.h"
#include "utils.h"

#define MAX_ACCOUNT_LEN 200
#define MAX_DATE_LEN 100
#define MAX_DESC_LEN 100

typedef struct Transaction
{
    very_long_int account;
    Date date;
    float amount;
    char remarks[MAX_DESC_LEN];

} Transaction;

void appendTransactionToFile(struct Transaction transaction);
void readTransactionsFromFile();



int createTransaction(float amount, char *remarks, very_long_int account_number,  Transaction *transaction); // returntype indicates errorcode
void listTransactions();
void getTransactionsForAccount(char *account);
void getTransactionsFromDate(char *date);

void print_transaction(Transaction t);

void print_transactions(Transaction* transactions, int size);

int get_transactions_by_acc_number(very_long_int acc_number, Transaction *transactions);

#endif
