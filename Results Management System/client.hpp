//
//  client.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/13.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef client_hpp
#define client_hpp

#include <stdio.h>
#include "global.hpp"

class User_interface
{
public:
    typedef unsigned short int type;
    User_interface() = default;
    ~User_interface() = default;
    void teacher_serv();
    void student_serv();
    bool login();
    void show();
private:
    type userType = 0;
    Person_ptr user_ptr;
    Student_ptr stu_ptr;
    Teacher_ptr tea_ptr;
    static constexpr type isStudent = 1;
    static constexpr type isTeacher = 2;
};

#endif /* client_hpp */
