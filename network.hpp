//
//  network.h
//  Results Management System
//
//  Created by YeWenting. on 16/6/15.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef network_hpp
#define network_hpp

constexpr unsigned int MAX_CONTENT_LENGTH = 512;
constexpr unsigned int MAX_PASSWORD_LENGTH = 20;

struct Request_info
{
    typedef unsigned int size;
    unsigned short int type = 0;
};

struct Message
{
    short int ack = 0;
    char content[MAX_CONTENT_LENGTH] = "";
};

void recv_request(int, Request_info &);
void recv_message(int, Message &);
void send_message(int &, const char *);
bool isclosed(int);

constexpr unsigned short int port = 1234;
extern int userSock;

typedef unsigned short int clientType;
constexpr clientType isStudent = 1;
constexpr clientType isTeacher = 2;

constexpr unsigned short int LOGIN = 0;
constexpr unsigned short int PRINT_ELECTIVE_COURSE = 1;
constexpr unsigned short int ATTEND_COURSE = 2;
constexpr unsigned short int CANCEL_COURSE = 3;
constexpr unsigned short int PRINT_SCORE_TABLE = 4;
constexpr unsigned short int MODIFY_SCORE = 5;
constexpr unsigned short int GET_INFO = 6;
#endif /* network_hpp */
