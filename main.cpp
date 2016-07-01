//
//  server.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/15.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//
// port 限定

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <sys/ioctl.h>

#include "csapp.h"
#include "global.hpp"
#include "network.hpp"
#include "person.hpp"
#include "system.hpp"
#include "server.hpp"

int main(int argc, const char * argv[])
{
    Server myServer(argc, argv);
    myServer.run();
    return 0;
}
