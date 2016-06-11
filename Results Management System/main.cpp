//
//  main.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/28.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "system.hpp"

int main(int argc, const char * argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::invalid_argument;
    constexpr unsigned short int isStudent = 1;
    constexpr unsigned short int isTeacher = 2;
    Result_system &system = Result_system::get_instance();
    
    for (auto i = 0; i < 3; i++, cout<<endl);
    cout << "Welcome to the results management system, designed by YeWenting.\nFor any problem, please contact me via Wenting_Ye@Outlook.com" << endl << "\n1 to login as a student;\n2 to login as a teacher;\n3 to exit." << endl;;
    
    unsigned short int input, userType = 0;
    Person_ptr user_ptr;
    Student_ptr std_ptr;
    Teacher_ptr tea_ptr;
    
    while (cin >> input)
    {
        try
        {
            if (input > 3 || !cin.good()) throw std::invalid_argument("Command invalid!");
            if (input == 3) break;
            Person::seq userId;
            std::string password;
            cout << "\nPlease input your ID and password in ONE LINE" << endl;
            cin.clear();
            cin >> userId >> password;
            user_ptr = system.get_person(userId);
            if (!user_ptr->authorize(password))
                throw invalid_argument("Your id/password is incorrect.");
            if (input == isStudent)
            {
                userType = isStudent;
                std_ptr = std::dynamic_pointer_cast<Student> (user_ptr);
            }
            else
            {
                userType = isTeacher;
                tea_ptr = std::dynamic_pointer_cast<Teacher> (user_ptr);
            }
            
            user_ptr->display_info(cout, INCREASE_BY_SCORE);
//            user_ptr->display_info(cout, DECREASE_BY_SCORE);
            
            
            if (userType == isStudent)
            {
                cout << "\n1 to view the elective course that is available for you;\n2 to attend a course;\n3 to cancel a course.\n4 to exit." << endl;
                while (cin >> input)
                {
                    if (input == 1)
                        system.print_available_course(*std_ptr, cout);
                    else if (input == 2)
                        std_ptr->enroll_course();
                    else if (input == 3)
                        std_ptr->cancel_course();
                    else break;
                    
                    cout << "\n1 to view the elective course that is available for you;\n2 to attend a course;\n3 to cancel a course.\n4 to exit." << endl;
                }
            }
            
            else
            {
                cout << "\n1 to view score table;\n2 to modify someone's grade;\n3 to exit." << endl;
                while (cin >> input)
                {
                    if (input == 1)
                    {
                        tea_ptr->check_score(cin, cout,INCREASE_BY_SCORE);
                        tea_ptr->check_score(cin, cout,DECREASE_BY_SCORE);
                    }
                    else if (input == 2)
                        tea_ptr->modify_score(cin, cout);
                    else break;
                    
                    cout << "\nInput 1 to view score table;\n2 to modify someone's score;\n3 to exit." << endl;
                }
            }
        }
        
        catch (std::invalid_argument err)
        {
            cout << err.what() << "\nTry again? Enter y or n" <<endl;
            char c;
            cin.clear();
            cin >> c;
            if (!cin || c == 'n') break;
            continue;
        }
        cout << "\n1 to login as a student;\n2 to login as a teacher;\n3 to exit." << endl;;
    }
    cout << "\n\nThanks for using, goodbye:)" << endl;
    return 0;
}
