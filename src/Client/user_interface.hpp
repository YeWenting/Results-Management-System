//
//  user_interface.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/13.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef user_interface_hpp
#define user_interface_hpp

#include <stdio.h>
#include <string>
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"

class User_interface
{
public:
    User_interface() = default;
    ~User_interface() = default;
    void show();
private:
    clientType userType = 0;
    Person_ptr user_ptr;
    Student_ptr stu_ptr;
    Teacher_ptr tea_ptr;
    
/* the interface to the user */
    bool login();
    void teacher_serv();
    void student_serv();
    
/* to send the user's request */
    void do_display_info(Score_mode mode = INCREASE_BY_SCORE);
    void do_print_elective_course();
    void do_attend_course();
    void do_cancel_course();
    void do_check_score();
    void do_modify_score();
    void do_login(clientType, size_t, std::string);
};

#endif /* user_interface_hpp */
