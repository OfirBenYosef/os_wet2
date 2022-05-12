//
//  main.cpp
//  
//
//  Created by Ofir Ben Yosef on 12/05/2022.
//
#include <list>
#include <stdio.h>
#include "Bank.h"
//list<account> Bank;

int main(int argc, char *argv[]){
    if (argc == 1) {
        cout << "illegal arguments" << endl;
        return(1);
    }
    int num_of_ATMs = argc - 1;
    pthread_t* threads_ATMs = new pthread_t[num_of_ATMs];
    
    return 0;
}
