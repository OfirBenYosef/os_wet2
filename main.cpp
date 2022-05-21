//
//  main.cpp
//  
//
//  Created by Ofir Ben Yosef on 12/05/2022.
//
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <utility>
#include <string>
#include <list>
#include "Bank.h"
#include "atm.h"
//list<account> Bank;

int main(int argc, char *argv[]){
    if (argc == 1|| atoi(argv[1]) != argc - 2) {
        cout << "illegal arguments" << endl;
        return(1);
    }
    int num_of_ATMs = argc - 2;
    
    pthread_t* threads_ATMs = new pthread_t[num_of_ATMs];
    pthread_t thread_print ;
    pthread_t thread_commission;
    
    if (pthread_create(&thread_print, nullptr, print_accounts,nullptr) != 0) {
        perror("pthread_create has failed");
        exit(1);
    }
    if (pthread_create(&thread_commission, nullptr, commission,nullptr) != 0) {
        perror("pthread_create has failed");
        exit(1);
    }
    pair<int, string>* ids = new pair<int, string>[num_of_ATMs];
    for (int i = 0; i < num_of_ATMs; i++)
    {
        string file(argv[i + 2]);
        ids[i].first = i + 1;
        ids[i].second = file;
        if (pthread_create(&(threads_ATMs[i]), nullptr, open_file, &ids[i]) != 0) {
            perror("pthread_create has failed");
            exit(1);
        }
    }
    for (int i = 0; i < num_of_ATMs; i++)
    {
        if (pthread_join(threads_ATMs[i], nullptr) != 0) {
            perror("pthread_join has failed");
            exit(1);
        }
    }

    all_atm_term = true;
    if (pthread_join(thread_print, nullptr) != 0) {
        perror("pthread_join has failed");
        exit(1);
    }
    if (pthread_join(thread_commission, nullptr) != 0) {
        perror("pthread_join has failed");
        exit(1);
    }
     delete[] threads_ATMs;
    delete[] ids;
    return 0;
}
