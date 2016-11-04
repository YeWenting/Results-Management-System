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

#include "../Shared/csapp.h"
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"
#include "../Library/person.hpp"
#include "../Library/system.hpp"
#include "server.hpp"

int main(int argc, const char * argv[])
{
    Server myServer(argc, argv);
    myServer.run();
    return 0;
}
