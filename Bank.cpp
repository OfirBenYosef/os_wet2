//
//  Bank.cpp
//  Bank
//
//  Created by Ofir Ben Yosef on 03/05/2022.
//

#include "Bank.h"
using namespace std;
//add func that check if the acc id is taken
account::account(int ATM,int account_id,int password,int balance){
      this->account_id = account_id;
      this->password = password;
      this->balance = balance;
    cout<<"<"<<ATM<<">: New account id is <"<<this->account_id<<"> with password <"<<this->password<<"> and initial balance <"<<this->balance<<">"<<endl;
}

void account::deposit(int ATM,int password,int balance_new){
    if(this->password == password){
      this->balance = this->balance + balance_new;
        cout<<"<"<<ATM<<": Account <"<<this->account_id<<"> new balance is <"<<this->balance<<"> after <"<<balance_new<<"> $ was deposited"<<endl;
        return;
    }
    cout <<"Error <"<<ATM<<">: Your transaction failed – password for account id <"<<this->account_id<<"> is incorrect"<<endl;
}
void account::withdrew(int ATM,int password,int balance_new){
    if(this->password == password){
        if(this->balance >= balance_new){
           this->balance = this->balance - balance_new;
            cout<<"<"<<ATM<<": Account <"<<this->account_id<<"> new balance is <"<<this->balance<<"> after <"<<balance_new<<"> $ was withdrew"<<endl;
        }
        else{
            cout <<"Error <"<<ATM<<">: Your transaction failed – password for account id <"<<this->account_id<<"> is incorrect"<<endl;
        }
        return;
    }
    cout <<"Error <"<<ATM<<">: Your transaction failed – account id <"<<this->account_id<<"> balance is lower than <"<<this->balance<<">"<<endl;
}
void account::find_balance(int ATM,int password){
    if(this->password == password){
        cout<<"<"<<ATM<<">: Account <"<<this->account_id<<"> balance is <"<<this->balance<<">"<<endl;
        return;
    }
    cout <<"Error <"<<ATM<<">: Your transaction failed – password for account id <"<<this->account_id<<"> is incorrect"<<endl;
}
void account::close_account(int ATM,int password){
    if(this->password == password){
        cout<<"<"<<ATM<<">: Account <"<<this->account_id<<"> is now closed. Balance was <"<<this->balance<<">"<<endl;
        return;
    }
    cout <<"Error <"<<ATM<<">: Your transaction failed – password for account id <"<<this->account_id<<"> is incorrect"<<endl;
}
void account::print_account(){
    cout <<"Account" <<this->account_id<<": Balance – "<<this->balance <<"$, Account Password – "<<this->password<<endl;
}
