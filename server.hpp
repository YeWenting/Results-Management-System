//
//  server.h
//  Results Management System
//
//  Created by YeWenting. on 16/6/17.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef server_h
#define server_h

#include <vector>

#include "global.hpp"

constexpr unsigned short int NO_LOGIN = 0;
constexpr unsigned short int NO_CLIENT = 1;
constexpr unsigned short int STUDENT = 2;
constexpr unsigned short int TEACHER = 3;
constexpr int MAX_CLIENT = 100;

struct Client_info
{
    short int status = 0;
    Person_ptr data;
};

class Server
{
public:
    Server();
    ~Server();
    void run();
private:
    int listenSock, dataSock, maxfd;
    fd_set fds, rfds;
    std::vector <Client_info> client;
    int receive_data(int);
    void do_login(int);
    void do_get_info(int);
    void send_error(int, const char *);
    void log_event();
};


#endif /* server_h */
