//
//  atm.h
//  
//
//  Created by Ofir Ben Yosef on 14/05/2022.
//

#ifndef atm_h
#define atm_h

#include <stdio.h>
#include "Bank.h"
#include<list>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include "lock.h"


void* open_file(void * info);
#endif /* atm_h */
