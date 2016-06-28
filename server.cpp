//
//  server.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/17.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <sys/ioctl.h>

#include "csapp.h"
#include "global.hpp"
#include "network.hpp"
#include "person.hpp"
#include "system.hpp"
#include "server.hpp"
#include <cstring>

Server::Server()
{
    struct sockaddr_in cliAddr;
    socklen_t cliLen= sizeof(cliAddr);
    
    
    //    /* Check arguments */
    //    if (argc != 2) {
    //        fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
    //        exit(0);
    //    }
    
    //start serving
    //port = atoi(argv[1]);
    listenSock = Open_listenfd(port);
    std::cout << "ready" << std::endl;
    maxfd = listenSock + 1;
    FD_ZERO(&fds);
    FD_SET(listenSock, &fds);
    client = std::vector <Client_info>(100);
}

Server::~Server()
{
    client.clear();
}

void Server::run()
{
    
    while (1)
    {
        memcpy(&rfds, &fds, sizeof(fds));
        if (Select(maxfd, &rfds, 0, 0, NULL) <= 0) break;
        
        // A new client
        if (FD_ISSET(listenSock, &rfds))
        {
            dataSock = Accept(listenSock, 0, 0);
            FD_SET(dataSock, &fds);
            if (maxfd <= dataSock) maxfd = dataSock + 1;
            client[dataSock].status = NO_LOGIN;
        }
        for (int fd = 0; fd < maxfd; fd++)
        {
            if (fd !=listenSock && FD_ISSET(fd, &rfds))
            {
                if (isclosed(fd))
                {
                    Close(fd);
                    FD_CLR(fd, &fds);
                    client[fd].status = NO_CLIENT;
                }
                else receive_data(fd);
            }
            //   printf("%d", fd);
        }
    }
    Close(listenSock);
    Close(dataSock);
}

void Server::send_error(int fd, const char *s)
{
    Message error;
    error.ack = -1;
    strcpy(error.content, s);
    Rio_writen(fd, &error, sizeof(error));
}

void Server::do_login(int fd)
{
    Result_system &system = Result_system::get_instance();
    size_t id;
    unsigned short int type;
    std::string password;
    
    Rio_readn(fd, &type, sizeof(type));
    Rio_readn(fd, &id, sizeof(id));
    Rio_readn(fd, &password, MAX_PASSWORD_LENGTH);
    
    try
    {
        Person_ptr user_ptr = system.get_person(id);
        if (!user_ptr->authorize(password))
            throw std::invalid_argument("Your id/password is incorrect.");
        client[fd].status = type;
        client[fd].data = user_ptr;
        Message mes;
        Rio_writen(fd, &mes, sizeof(mes));
    }
    catch (std::invalid_argument err)
    {
        send_error(fd, err.what());
    }
}

void Server::do_get_info(int fd)
{
    Score_mode mode;
    Rio_readn(fd, &mode, sizeof(mode));
    
    std::stringstream ss;
    (client[fd].data)->display_info(ss, mode);
    
//    char content[MAX_CONTENT_LENGTH];
//    strcpy(content, ss.str().c_str());
//    std::cout << content << std::endl;
//    std::cout << rio_writen(fd, content, MAX_CONTENT_LENGTH) << std::endl;
    
    std::string content;
    content.assign(ss.str());
    std::cout << rio_writen(fd, &content, MAX_CONTENT_LENGTH) << std::endl;
}

int Server::receive_data(int sock)
{
    int client_num;
    //    printf("get into receive data\n");
    //    char s[50] = "";
    //    if (Rio_readn(sock, s, 10) == 0) return WRONG;
    //    if (s[0] != '\0')
    //    {
    //        printf("%d ", sock);
    //        puts(s);
    //    }
    //    return RIGHT;
    Request_info req;
//    Rio_readn(sock, &req, sizeof(req));
//    std::string s = "hello\n\nhello";
//    Rio_writen(sock, &s, 20);
    switch (req.type)
    {
        case LOGIN: do_login(sock);
            break;
            //        case PRINT_SCORE_TABLE: do_print_score_table(sock, mes.length);
            //        case ATTEND_COURSE: do_attend_course(sock, mes.length);
            //        case CANCEL_COURSE: do_cancel_course(sock, mes.length);
            //        case PRINT_ELECTIVE_COURSE: do_print_elective_course(sock, mes.length);
            //        case MODIFY_SCORE: do_modify_score(sock, mes.length);
        case GET_INFO: do_get_info(sock);
            break;
    }
    return 1;
}