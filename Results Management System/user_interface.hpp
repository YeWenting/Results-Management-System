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
#include "global.hpp"
#include "network.hpp"

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
    
    std::string get_info(Score_mode mode = INCREASE_BY_SCORE);
    void teacher_serv();
    void student_serv();
    void request_login(clientType, size_t, std::string);
    bool login();
};

#endif /* user_interface_hpp */
