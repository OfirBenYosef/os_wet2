//
//  Bank.cpp
//  Bank
//
//  Created by Ofir Ben Yosef on 03/05/2022.
//

#include "Bank.h"
list<account> Bank;
//add func that check if the acc id is taken
account::account(int account_id,int password,int balance){
      this->account_id = account_id;
      this->password = password;
      this->balance = balance;
}

void account::deposit(int ATM,int password,int balance_new){
    if(this->password == password){
      this->balance = this->balance + balance_new;
        cout<<ATM<<": Account "<<this->account_id<<" new balance is "<<this->balance<<" after "<<balance_new<<" $ was deposited"<<endl;
        return;
    }
    cout <<"Error "<<ATM<<": Your transaction failed – password for account id "<<this->account_id<<" is incorrect"<<endl;
}
void account::withdrew(int ATM,int password,int balance_new){
    if(this->password == password){
        if(this->balance >= balance_new){
           this->balance = this->balance - balance_new;
            cout<<ATM<<": Account <"<<this->account_id<<" new balance is <"<<this->balance<<" after "<<balance_new<<" $ was withdrew"<<endl;
        }
        else{
            cout <<"Error "<<ATM<<": Your transaction failed – account id "<<this->account_id<<" balance is lower than "<<this->balance<<endl;
        }
        return;
    }
    cout <<"Error "<<ATM<<": Your transaction failed – password for account id "<<this->account_id<<" is incorrect"<<endl;
}
void account::find_balance(int ATM,int password){
    if(this->password == password){
        cout<<ATM<<": Account "<<this->account_id<<" balance is <"<<this->balance<<endl;
        return;
    }
    cout <<"Error "<<ATM<<": Your transaction failed – password for account id "<<this->account_id<<" is incorrect"<<endl;
}
bool account::close_account(int ATM,int password){
    //delete from the accout list
    if(this->password == password){
        cout<<ATM<<": Account "<<this->account_id<<" is now closed. Balance was "<<this->balance<<endl;
        return true;
    }
    cout <<"Error "<<ATM<<": Your transaction failed – password for account id "<<this->account_id<<" is incorrect"<<endl;
    return false;
}
void account::print_account(){
    cout <<"Account" <<this->account_id<<": Balance – "<<this->balance <<"$, Account Password – "<<this->password<<endl;
}

int random_commission(){
    time_t now = time(0);
    srand(now);
    int a[5] = {1,2,3,4,5};
    int temp = now%5;
    return a[temp];
}

int account::take_commission(int amount_of_commission){
    double commission = ((this->balance)*amount_of_commission)/100;
    int r_commission = round(commission);
    this->balance  = this->balance - r_commission;
    cout<< "Bank: commissions of "<< amount_of_commission <<" % were charged, the bank gaind "<<r_commission << " $ from account " << this->account_id <<endl;
    return r_commission;
}

void print_no_account_error(int ATM, int account_id){
    cout <<"Error "<<ATM<<": Your transaction failed – account id"<<account_id<<"does not exist"<<endl;
}

bool account::take_transaction(int ATM,int account_id,int password,int amount){
    if(this->password == password){
        if(this->balance >= amount){
           this->balance = this->balance - amount;
            return true;
        }
        else{
            cout <<"Error "<<ATM<<": Your transaction failed – account id "<<this->account_id<<" balance is lower than "<<amount<<endl;
        }
        return false;
    }
    cout <<"Error "<<ATM<<": Your transaction failed – password for account id "<<this->account_id<<" is incorrect"<<endl;
    return false;
}
void account::give_transaction(int ATM,int account_id,int amount){
    this->balance = this->balance + amount;
}

void open_account(int ATM,int account_id,int password,int balance){
    list<account>::iterator it_acc;
    if(!find_account(account_id,it_acc)){
        account *new_account = new account(account_id, password,balance);
        Bank.push_back(*new_account);
        cout<<ATM<<": New account id is "<<account_id<<"> with password "<<password<<" and initial balance "<<balance<<endl;
        return;
    }
    cout<<"Error "<<ATM<<": Your transaction failed – account with the same id exists"<<endl;
}
bool find_account(int account_id,list<account>::iterator it_t){
    for(list<account>::iterator it = Bank.begin(); it != Bank.end(); it++){
        if(it->account_id == account_id){
            it_t = it;
            return true;
        }
    }
    return false;
}
void transaction(int ATM,int account_id,int password,int target,int amount){
    list<account>::iterator it_acc;
    list<account>::iterator it_target;
    
    bool acc_1 = find_account(account_id,it_acc);
    bool acc_2 = find_account(target,it_target);
    

    if(!acc_1 ){
        print_no_account_error(ATM,account_id);
    }
    if(!acc_2 ){
        print_no_account_error(ATM,target);
    }
    if(!acc_1 || !acc_2){
        return;
    }
    else if(it_acc->take_transaction(ATM,account_id,password,amount)){
        it_target->give_transaction(ATM,target,amount);
        cout <<ATM<< ": Transfer "<< amount<<" from account "<<account_id <<" to account " <<target<<" new account balance is "<<it_acc->balance<<" new target account balance is "<<it_target->balance<<endl;
    }
}

void close_account_shell(int ATM,int account_id,int password){
    list<account>::iterator it_acc;
    if(find_account(account_id,it_acc)){
        if(it_acc->close_account(account_id,password)){
            Bank.erase(it_acc);
            return;
        }
        else{
            perror("Error");
        }
    }
    print_no_account_error(ATM,account_id);
}
bool account::operator <(const account & account_2)const{
    return this->account_id < account_2.account_id;
}
void print_accounts(){
    while(1){
        Bank.sort();
        printf("\033[2J\033[1;1H");
        for(list<account>::iterator it = Bank.begin(); it != Bank.end(); it++){
            it->print_account();
        }
        usleep(500000);
    }
}
