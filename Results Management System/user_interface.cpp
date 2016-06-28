//
//  user_interface.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/13.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "system.hpp"
#include "user_interface.hpp"
#include "global.hpp"
#include "csapp.h"
#include "network.hpp"

void User_interface::show()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::invalid_argument;
    
    while (1)
    {
        system("clear");
        for (auto i = 0; i < 2; i++, cout<<endl);
        cout << "Welcome to the results management system, designed by YeWenting.\nFor any problem, please contact me via Wenting_Ye@Outlook.com" << endl;
        
        if (login() == true)
        {
            cout << get_info() << endl;
            if (userType == isStudent)
                student_serv();
            else
                teacher_serv();
        }
        else break;
    }
    cout << "\n\nThanks for using, goodbye:)" << endl;
}

std::string User_interface::get_info(Score_mode mode)
{
    std::cout << "send info request!" << std::endl;
    Request_info req;
    req.type = GET_INFO;
    Rio_writen(userSock, &req, sizeof(req));
    Rio_writen(userSock, &mode, sizeof(mode));
    
//    char content[MAX_CONTENT_LENGTH];
//    std::cout << Rio_readn(userSock, content, MAX_CONTENT_LENGTH) << std::endl;
//    std::cout << content;
    std::string content;
    std::cout << Rio_readn(userSock, &content, MAX_CONTENT_LENGTH) << std::endl;
    return content;
}

void User_interface::request_login(clientType loginType, size_t id, std::string password)
{
    Request_info req;
    req.type = LOGIN;
    
    Rio_writen(userSock, &req, sizeof(req));
//    loginType += 1;
    Rio_writen(userSock, &loginType, sizeof(loginType));
    Rio_writen(userSock, &id, sizeof(id));
    Rio_writen(userSock, &password, MAX_PASSWORD_LENGTH);
    
//    std::string s;
//    Rio_readn(userSock, &s, 20);
//    std::cout << s << std::endl;
    Message mes;
    Rio_readn(userSock, &mes, sizeof(mes));
    // login successfully will return a ack >= 0
    if (mes.ack < 0) throw std::invalid_argument("Your id/password is incorrect.");
}

bool User_interface::login()
{
    Result_system &system = Result_system::get_instance();
    using namespace std;
    
    while (1)
    {
        try
        {
            cout << "\n1 to login as a student;\n2 to login as a teacher;\n3 to exit." << endl;;
            cin >> userType;
            if (cin.fail()) throw std::invalid_argument("Please input a integer between 1~3!");
            if (userType > 3) throw std::invalid_argument("User type invalid!");
            if (userType == 3) return WRONG;
            
            Person::seq userId;
            std::string password;
            cout << "\nPlease input your ID and password in ONE LINE" << endl;
            cin >> userId >> password;
            request_login(userType, userId, password);
            return RIGHT;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
    return RIGHT;
}

void User_interface::student_serv()
{
    unsigned short int query, order = INCREASE_BY_SCORE;
    Result_system &system = Result_system::get_instance();
    using namespace std;
    
    stu_ptr = std::dynamic_pointer_cast<Student> (user_ptr);
    
    stu_ptr->display_info(cout, order);
    while (true)
    {
        try
        {
            cout << "\n1 to view the elective course that is available for you;\n2 to attend a course;\n3 to cancel a course.\n4 to change score order,\n5 to exit." << endl;
            cin >> query;
            if (cin.fail()) throw std::invalid_argument("Please input a integer between 1 ~ 3!");
            
            if (query == 1)
                system.print_available_course(*stu_ptr, cout);
            else if (query == 2)
                stu_ptr->enroll_course();
            else if (query == 3)
                stu_ptr->cancel_course();
            else if (query == 4)
            {
                order = !order;
                stu_ptr->display_info(cout, order);
            }
            else break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

void User_interface::teacher_serv()
{
    unsigned short int query, order;
    using namespace std;
    
    tea_ptr = std::dynamic_pointer_cast<Teacher> (user_ptr);
    tea_ptr->display_info(cout);
    while (true)
    {
        try
        {
            cout << "\n1 to view score table;\n2 to modify someone's grade;\n3 to exit." << endl;
            cin >> query;
            if (cin.fail()) throw std::invalid_argument("Please input a integer between 1 ~ 3!");
            
            if (query == 1)
            {
                cout << "Which order do you prefer, 0 for increasing and 1 for decreasing?" << endl;
                cin >> order;
                if (cin.fail() || order > 1) throw std::invalid_argument("Please input a integer between 0 ~ 1!");
                tea_ptr->check_score(cin, cout, order);
            }
            else if (query == 2)
                tea_ptr->modify_score(cin, cout);
            else break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}