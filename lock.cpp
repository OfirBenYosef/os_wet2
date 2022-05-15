//
//  lock.cpp
//  
//
//  Created by Ofir Ben Yosef on 15/05/2022.
//

#include "lock.h"
/**************************************************************************************************/

locker::locker()
{
    readers_counter = 0;
    if (pthread_mutex_init(&read, nullptr) != 0) {
        perror("pthread_mutex_init has failed");
        exit(1);
    }
    if (pthread_mutex_init(&write, nullptr) != 0) {
        perror("pthread_mutex_init has failed");
        exit(1);
    }
}

locker::~locker()
{
    if (pthread_mutex_destroy(&read) != 0) {
        perror("pthread_mutex_destroy has failed");
        exit(1);
    }
    if (pthread_mutex_destroy(&write) != 0) {
        perror("pthread_mutex_destroy has failed");
        exit(1);
    }
}
void locker::add_reader(){}
void locker::remove_reader(){}
void locker::add_writer(){}
void locker::remove_writer(){}
/**************************************************************************************************/
log::log()
{
    log_file.open("log.txt", ofstream::out | ofstream::trunc);
}

log::~log()
{
    log_file.close();
}

void log::update_log(string txt)
{
    lck.add_writer();
    log_file << txt << endl;
    lck.remove_writer();
}
