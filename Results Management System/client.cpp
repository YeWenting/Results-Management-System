//
//  main.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/28.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//
#include <stdio.h>

#include "csapp.h"
#include "global.hpp"
#include "user_interface.hpp"
#include "network.hpp"

int userSock;

int main(int argc, const char * argv[])
{
    User_interface window;
    userSock = Open_clientfd("127.0.0.1", port);
    
    window.show();
    return 0;
}
//
//int main(int argc, const char * argv[])
//{
//    int sock = Open_clientfd("127.0.0.1", port);
//    char s[10] = "1";
//    int x = sizeof(s);
//    Rio_writen(sock, s, sizeof(s));
//    printf("%d\n", x);
//    while (1);
//    Close(sock);
//    return 0;
//}
