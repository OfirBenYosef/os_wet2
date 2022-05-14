//
//  main.cpp
//  
//
//  Created by Ofir Ben Yosef on 12/05/2022.
//
#include <list>
#include <stdio.h>
#include "Bank.h"
#include "atm.h"
//list<account> Bank;

int main(int argc, char *argv[]){
    if (argc == 1) {
        cout << "illegal arguments" << endl;
        return(1);
    }
    int num_of_ATMs = argc - 1;
    pthread_t* threads_ATMs = new pthread_t[num_of_ATMs];
    pair<int, string>* ids = new pair<int, string>[num_of_ATMs];
    for (int i = 0; i < num_of_ATMs; i++)
    {
        string file(argv[i + 1]);
        ids[i].first = i + 1;
        ids[i].second = file;
       /* if (pthread_create(&(threads_ATMs[i]), nullptr, //todo, &ids[i]) != 0) {
            perror("pthread_create has failed");
            exit(1);
        }*/
    }
    return 0;
}
