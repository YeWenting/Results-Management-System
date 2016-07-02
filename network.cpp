//
//  network.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/15.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <string>
#include <sstream>

#include "network.hpp"
#include "csapp.h"

/*
 send the "request" packet
*/
void send_request(int fd, unsigned short int t)
{
    Request_info req;
    req = t;
    Rio_writen(fd, &req, sizeof(req));
}


void recv_message(int fd, std::ostream &os)
{
    Message mes;
    Rio_readn(fd, &mes, sizeof(Message));
    if (mes.ack < 0) throw std::invalid_argument(mes.content);
    else os << mes.content <<std::endl;
}

/*
  send the "message" packet
*/
void send_message(int fd, const char *content)
{
    Message mes;
    if (content == NULL) mes.ack = -1;
    else mes.ack = 0;
    strcpy(mes.content, content);
    Rio_writen(fd, &mes, sizeof(mes));
}

void send_message(int fd, std::stringstream &os)
{
    Message mes;
    strcpy(mes.content, os.str().c_str());
    
    Rio_writen(fd, &mes, sizeof(mes));
}

void send_error(int fd, const char *s)
{
    Message error;
    error.ack = -1;
    strcpy(error.content, s);
    Rio_writen(fd, &error, sizeof(error));
}

bool isclosed(int sock) {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock, &rfd);
    timeval tv = { 0 };
    select(sock+1, &rfd, 0, 0, &tv);    //判断fd状态是否可读
    if (!FD_ISSET(sock, &rfd))
        return false;
    int n = 0;
    ioctl(sock, FIONREAD, &n);          //判断fd还有东西读吗
    return n == 0;
}