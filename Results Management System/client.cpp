//
//  client.cpp
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
#include <curses.h>

#include "system.hpp"
#include "client.hpp"
#include "global.hpp"

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
            user_ptr = system.get_person(userId);
            if (!user_ptr->authorize(password))
                throw invalid_argument("Your id/password is incorrect.");
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
    type query, order = INCREASE_BY_SCORE;
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
    type query, order;
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