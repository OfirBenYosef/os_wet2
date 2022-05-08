//
//  Bank.hpp
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

using namespace std;

class account{
public:
    int account_id;
    int password;
    int balance;
    
    account(int ATM,int account_id,int password,int balance);
    void deposit(int ATM,int password,int balance_new);
    void withdrew(int ATM,int password,int balance_new);
    void find_balance(int ATM,int password);
    void close_account(int ATM,int password);
    void print_account();
};

#endif /* Bank_h */
