//
//  Bank.cpp
//  Bank
//
//  Created by Ofir Ben Yosef on 03/05/2022.
//

#include "Bank.h"
list<account> Bank;
int bank_account = 0;
locker atm_locker;
logger out_log;
bool all_atm_term = false;
//add func that check if the acc id is taken
account::account(int account_id,int password,int balance,locker acc_lock){
      this->account_id = account_id;
      this->password = password;
      this->balance = balance;
      this->acc_lock = acc_lock;
}
account::~account(){
}

void account::deposit(int ATM,int password,int balance_new){

    if(this->password == password){
      this->balance = this->balance + balance_new;
        out_log.update_log(to_string(ATM)+": Account "+to_string(this->account_id)+" new balance is "+to_string(this->balance)+" after "+to_string(balance_new)+" $ was deposited");
        return;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – password for account id "+to_string(this->account_id)+" is incorrect");
}
void account::withdrew(int ATM,int password,int balance_new){
    if(this->password == password){
        if(this->balance >= balance_new){
           this->balance = this->balance - balance_new;
            out_log.update_log(to_string(ATM)+": Account "+to_string(this->account_id)+" new balance is "+to_string(this->balance)+" after "+to_string(balance_new)+" $ was withdrew");
        }
        else{
            out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – account id "+to_string(this->account_id)+" balance is lower than "+to_string(this->balance));
        }
        return;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – password for account id "+to_string(this->account_id)+" is incorrect");
}
void account::find_balance(int ATM,int password){
    if(this->password == password){
        out_log.update_log(to_string(ATM)+": Account "+to_string(this->account_id)+" balance is "+to_string(this->balance));
        return;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – password for account id "+to_string(this->account_id)+" is incorrect");
}
bool account::close_account(int ATM,int password){
    //delete from the accout list
    if(this->password == password){
        out_log.update_log(to_string(ATM)+": Account "+to_string(this->account_id)+" is now closed. Balance was "+to_string(this->balance));
        return true;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – password for account id "+to_string(this->account_id)+" is incorrect");
    return false;
}
void account::print_account(){
    cout <<"Account " <<this->account_id<<": Balance – "<<this->balance <<"$, Account Password – "<<this->password<<endl;
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
    out_log.update_log( "Bank: commissions of "+ to_string(amount_of_commission) +" % were charged, the bank gaind "+to_string(r_commission) + " $ from account " +to_string(this->account_id));
    return r_commission;
}

void print_no_account_error(int ATM, int account_id){
        out_log.update_log("Error "+to_string(ATM)+" : Your transaction failed – account id "+to_string(account_id)+" does not exist");
}

bool account::take_transaction(int ATM,int account_id_g,int password_g,int amount_g){
    if(password == password_g){
        if(this->balance >= amount_g){
           this->balance = this->balance - amount_g;
            return true;
        }
        else{
            out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – account id "+to_string(this->account_id)+" balance is lower than "+to_string(amount_g));
        }
        return false;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – password for account id "+to_string(this->account_id)+" is incorrect");
    return false;
}
void account::give_transaction(int ATM,int account_id,int amount){
    this->balance = this->balance + amount;
}

void open_account(int ATM,int account_id,int password,int balance){
    list<account>::iterator it_acc;
    if(!find_account(account_id,it_acc)){
        locker new_l;
        account new_account(account_id, password,balance,new_l);
        //new_account();
        Bank.push_back(new_account);
        out_log.update_log(to_string(ATM)+": New account id is "+to_string(account_id)+" with password "+to_string(password)+" and initial balance "+to_string(balance));
        return;
    }
    out_log.update_log("Error "+to_string(ATM)+": Your transaction failed – account with the same id exists");
}
bool find_account(int account_id,list<account>::iterator &it_t){
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
        out_log.update_log(to_string(ATM)+ ": Transfer "+ to_string(amount)+" from account "+to_string(account_id)+" to account " +to_string(target)+" new account balance is "+to_string(it_acc->balance)+" new target account balance is "+to_string(it_target->balance));
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
void* print_accounts(void * nothing){
    while(1){
        if(all_atm_term){
            pthread_exit(nullptr);
        }
        Bank.sort();
        printf("\033[2J");
        printf("\033[1;1H");
        cout << "Current Bank Status" << endl;
        atm_locker.add_reader();
        for(list<account>::iterator it = Bank.begin(); it != Bank.end(); it++){
            it->acc_lock.add_reader();
            it->print_account();
            it->acc_lock.remove_reader();
        }
        cout<<"The Bank has "<<bank_account<<" $"<<endl;
        atm_locker.remove_reader();
        usleep(500000);
    }
    return nullptr;
}
void* commission(void * nothing){
    while(1){
        if(all_atm_term){
            pthread_exit(nullptr);
        }
        atm_locker.add_reader();
       // atm_locker.add_writer();
        int commission = random_commission();
        int bank_gain = 0;
        for(list<account>::iterator it = Bank.begin(); it != Bank.end(); it++){
            bank_gain += it->take_commission(commission);
        }
        bank_account += bank_gain;
        //atm_locker.remove_writer();
        atm_locker.remove_reader();
        sleep(3);
        
    }
    return nullptr;
}
