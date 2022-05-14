//
//  atm.cpp
//  
//
//  Created by Ofir Ben Yosef on 14/05/2022.
//

#include "atm.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#define MAX_ARGS 5
void* open_file(void * info){
    pair<int, string>* ATM_info = (pair<int, string>*)info;
    int ATM_id = ATM_info->first;
    string ATM_file = ATM_info->second;
    string line;
    ifstream atm_file(ATM_file);
    const char* delimiter = " ";
    while(getline(atm_file,line)){
        usleep(100000);
        char* args[MAX_ARGS];
        int n = line.length();
        char temp_line[n + 1];
        strcpy(temp_line,line.c_str());
        args[0] = strtok(temp_line, delimiter);
        for (int i=1; i<MAX_ARGS; i++)
        {
            args[i] = strtok(NULL, delimiter);
        }
        if(!strcmp(args[0],("O"))){
            open_account(ATM_id,atoi(args[1]),atoi(args[2]),atoi(args[3]));
            sleep(1);
        }
        else  if(!strcmp(args[0],"D")){
            list<account>::iterator it_acc;
            if(find_account(atoi(args[1]),it_acc)){
                it_acc->deposit(ATM_id,atoi(args[2]),atoi(args[3]));
            }
            else{
                print_no_account_error(ATM_id, atoi(args[1]));
            }
            sleep(1);
        }
        else  if(!strcmp(args[0],"W")){
            list<account>::iterator it_acc;
            if(find_account(atoi(args[1]),it_acc)){
                it_acc->withdrew(ATM_id,atoi(args[2]),atoi(args[3]));
            }
            else{
                print_no_account_error(ATM_id, atoi(args[1]));
            }
            sleep(1);
        }
        else  if(!strcmp(args[0],"B")){
            list<account>::iterator it_acc;
            if(find_account(atoi(args[1]),it_acc)){
                it_acc->find_balance(ATM_id,atoi(args[2]));
            }
            else{
                print_no_account_error(ATM_id, atoi(args[1]));
            }
            sleep(1);
        }
        else  if(!strcmp(args[0],"Q")){
            close_account_shell(ATM_id,atoi(args[1]),atoi(args[2]));
            sleep(1);
        }
        else  if(!strcmp(args[0],"T")){
            transaction(ATM_id,atoi(args[1]),atoi(args[2]),atoi(args[3]),atoi(args[4]));
            sleep(1);
        }
        else
        {
            perror("bad input");
            exit(1);
        }
        usleep(100000);
    }
    return nullptr;
}
