//
//  Bank.h
//  Bank
//
//  Created by Ofir Ben Yosef on 03/05/2022.
//

#ifndef Bank_h
#define Bank_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <list>
#include "lock.h"

using namespace std;

class account{
public:
    int account_id;
    int password;
    int balance;
    
    account(int account_id,int password,int balance);
    void deposit(int ATM,int password,int balance_new);
    void withdrew(int ATM,int password,int balance_new);
    void find_balance(int ATM,int password);
    bool close_account(int ATM,int password);
    void print_account();
    int take_commission(int amount_of_commission);
    bool take_transaction(int ATM,int account_id,int password,int amount);
    void give_transaction(int ATM,int account_id,int amount);
    bool operator <(const account & account_2)const;
};
void transaction(int ATM,int account_id,int password,int target,int amount);
bool find_account(int account_id,list<account>::iterator it_t);
void open_account(int ATM,int account_id,int password,int balance);
void print_no_account_error(int ATM, int account_id);
void close_account_shell(int ATM,int password,int account_id);
void print_accounts();
extern locker atm_locker;
extern list<account> Bank;
#endif /* Bank_h */
