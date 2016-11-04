//
//  main.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/28.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//
#include <stdio.h>

#include "csapp.h"
#include "../Shared/global.hpp"
#include "user_interface.hpp"
#include "network.hpp"
#include "csapp.h"

int userSock;

int main(int argc, const char * argv[])
{
    User_interface window;
    
    /* Check arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <server port>\n", argv[0]);
        exit(0);
    }
    
    /* connect to the server */
    int port = atoi(argv[2]);
    char addr[20];
    strcpy(addr, argv[1]);
    userSock = Open_clientfd(addr, port);
    
    window.show();
    return 0;
}
