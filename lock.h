//
//  lock.h
//  
//
//  Created by Ofir Ben Yosef on 15/05/2022.
//

#ifndef lock_h
#define lock_h

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

using namespace std;

class locker
{
public:
    int readers_counter;
    pthread_mutex_t read;
    pthread_mutex_t write;

    locker();
    ~locker();

    void add_reader();
    void remove_reader();
    void add_writer();
    void remove_writer();
};
class logger
{
public:
    ofstream log_file;
    locker lck;

    logger();
    ~logger();

    void update_log(string txt);
};
#endif /* lock_h */
