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

#include "../Library/system.hpp"
#include "user_interface.hpp"
#include "../Shared/global.hpp"
#include "../Shared/csapp.h"
#include "../Shared/network.hpp"
#include "../Library/course.hpp"

/**************************************
 * User interface routines
 **************************************/

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
            /* display the basic info */
            do_display_info();
            recv_message(userSock, std::cout);
            
            if (userType == isStudent)
                student_serv();
            else
                teacher_serv();
        }
        else break;
    }
    cout << "\n\nThanks for using, goodbye:)" << endl;
}

bool User_interface::login()
{
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
            do_login(userType, userId, password);
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
    using namespace std;
    
    while (true)
    {
        try
        {
            cout << "\n1 to view the elective course that is available for you;\n2 to attend a course;\n3 to cancel a course.\n4 to change score order,\n5 to exit." << endl;
            cin >> query;
            if (cin.fail()) throw std::invalid_argument("Please input a integer between 1 ~ 5!");
            
            /* process the user's requirement */
            switch (query)
            {
                case 1:
                    send_request(userSock, PRINT_ELECTIVE_COURSE);
                    break;
                case 2:
                    do_attend_course();
                    break;
                case 3:
                    do_cancel_course();
                    break;
                case 4:
                    order = !order;
                    do_display_info(order);
                    break;
                case 5:
                    return;
                default:
                    throw std::invalid_argument("Please input a integer between 1 ~ 5!");
            }
            
            /* recv the message from server */
            recv_message(userSock, std::cout);
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

void User_interface::teacher_serv()
{
    unsigned short int query;
    using namespace std;
    
    while (true)
    {
        try
        {
            cout << "\n1 to view score table;\n2 to modify someone's grade;\n3 to exit." << endl;
            cin >> query;
            if (cin.fail()) throw std::invalid_argument("Please input a integer between 1 ~ 3!");
            
            /* process the user's requirement */
            switch (query)
            {
                case 1:
                    do_check_score();
                    break;
                case 2:
                    do_modify_score();
                    break;
                case 3:
                    return;
                default:
                    throw std::invalid_argument("Please input a integer between 1 ~ 3!");
            }
            
            /* recv the message from server */
            recv_message(userSock, std::cout);
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

/******************************************
 * Wrappers for the request sending routines
 ******************************************/

void User_interface::do_display_info(Score_mode mode)
{
    send_request(userSock, GET_INFO);
    Rio_writen(userSock, &mode, sizeof(mode));
    
    system("clear");
}

void User_interface::do_login(clientType loginType, size_t id, std::string password)
{
    send_request(userSock, LOGIN);
    Rio_writen(userSock, &loginType, sizeof(loginType));
    Rio_writen(userSock, &id, sizeof(id));
    Rio_writen(userSock, &password, MAX_PASSWORD_LENGTH);
    
    Message mes;
    Rio_readn(userSock, &mes, sizeof(mes));
    /* login successfully will return a ack >= 0 */
    if (mes.ack < 0) throw std::invalid_argument(mes.content);
}

void User_interface::do_attend_course()
{
    Course::seq courseNum;
    std::cout << "Please input the course ID" << std::endl;
    std::cin >> courseNum;
    if (std::cin.fail()) throw std::invalid_argument("Please input a interger.");
    
    send_request(userSock, ATTEND_COURSE);
    Rio_writen(userSock, &courseNum, sizeof(courseNum));
}

void User_interface::do_cancel_course()
{
    Course::seq courseNum;
    std::cout << "Please input the course ID" << std::endl;
    std::cin >> courseNum;
    
    if (std::cin.fail()) throw std::invalid_argument("Please input a interger.");
    
    send_request(userSock, CANCEL_COURSE);
    Rio_writen(userSock, &courseNum, sizeof(courseNum));
}

void User_interface::do_check_score()
{
    unsigned short int order;
    Course::seq courseID;
    
    /* input the courseID and expected order */
    std::cout << "Please enter the course ID" <<std::endl;
    std::cin >> courseID;
    std::cout << "Which order do you prefer, 0 for increasing and 1 for decreasing?" << std::endl;
    std::cin >> order;
    if (std::cin.fail() || order > 1) throw std::invalid_argument("Please input a integer between 0 ~ 1!");
    
    /* send the request */
    send_request(userSock, PRINT_SCORE_TABLE);
    Rio_writen(userSock, &courseID, sizeof(courseID));
    Rio_writen(userSock, &order, sizeof(order));
}

void User_interface::do_modify_score()
{
    Course::seq course = 0;
    Person::seq student = 0;
    Course::score  newScore = 0;
    
    /* Read the data */
    std::cout << "Please input the course ID, student ID, and new score:" << std::endl;
    std::cin >> course >> student >> newScore;
    
    /* Send the Request info */
    send_request(userSock, MODIFY_SCORE);
    Rio_writen(userSock, &course, sizeof(course));
    Rio_writen(userSock, &student, sizeof(student));
    Rio_writen(userSock, &newScore, sizeof(newScore));
}
