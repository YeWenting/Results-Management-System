//
//  network.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/15.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <stdio.h>
#include <sys/ioctl.h>

#include "network.hpp"
#include "csapp.h"

/*
    receive the "request" and "message" packet
*/
void recv_request(int fd, Request_info &req)
{
    Rio_readn(fd, &req, sizeof(req));
}

/*
  send the "message" packet
*/
void send_message(int &fd, const char *content)
{
    Message mes;
    if (content == NULL) mes.ack = -1;
    else mes.ack = 0;
    strcpy(mes.content, content);
    Rio_writen(fd, &mes, sizeof(mes));
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