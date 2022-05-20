//
//  lock.cpp
//  
//
//  Created by Ofir Ben Yosef on 15/05/2022.
//

#include "lock.h"
using namespace std;
/**************************************************************************************************/

locker::locker()
{
    readers_counter = 0;
    if(pthread_mutex_init(&read, nullptr) != 0) {
        perror("pthread_mutex_init has failed");
        exit(1);
    }
    if(pthread_mutex_init(&write, nullptr) != 0) {
        perror("pthread_mutex_init has failed");
        exit(1);
    }
}

locker::~locker()
{
    if(pthread_mutex_destroy(&read) != 0) {
        perror("pthread_mutex_destroy has failed");
        exit(1);
    }
    if(pthread_mutex_destroy(&write) != 0) {
        perror("pthread_mutex_destroy has failed");
        exit(1);
    }
}
void locker::add_reader(){
    if(pthread_mutex_lock(&read) != 0) {
        perror("pthread_mutex_lock has failed");
        exit(1);
    }
    readers_counter++;
    if(readers_counter == 1) {
        if(pthread_mutex_lock(&write) != 0) {
            perror("pthread_mutex_lock has failed");
            exit(1);
        }
    }
    if(pthread_mutex_unlock(&read) != 0) {
        perror("pthread_mutex_unlock has failed");
        exit(1);
    }
}
void locker::remove_reader(){
    if(pthread_mutex_lock(&read) != 0) {
        perror("pthread_mutex_lock has failed");
        exit(1);
    }
    readers_counter--;
    if (readers_counter == 0) {
        if (pthread_mutex_unlock(&write) != 0) {
            perror("pthread_mutex_unlock has failed");
            exit(1);
        }
    }
    if (pthread_mutex_unlock(&read) != 0) {
        perror("pthread_mutex_unlock has failed");
        exit(1);
    }
}
void locker::add_writer(){
    if (pthread_mutex_lock(&write) != 0) {
        perror("pthread_mutex_lock has failed");
        exit(1);
    }
}

void locker::remove_writer(){
    if (pthread_mutex_unlock(&write) != 0) {
        perror("pthread_mutex_unlock has failed");
        exit(1);
    }
}
/**************************************************************************************************/
logger::logger()
{
    log_file.open("log.txt", ofstream::out | ofstream::trunc);
}

logger::~logger()
{
    log_file.close();
}

void logger::update_log(string txt)
{
    lck.add_writer();
    log_file << txt << endl;
    lck.remove_writer();
}
