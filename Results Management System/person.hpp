//
//  people.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef people_hpp
#define people_hpp

#include <stdio.h>

class Person
{
public:
    Person() = default;
    Person(const size_t& i, const std::string &n, const std::string &cl, const unsigned int &cla, std::vector <size_t> cou, const std::string &pa) : id(i), name(n), classNum(cla), college(cl), courseNum(cou), password(pa) {};
    ~Person() = default;
    virtual display_info() = 0;
    virtual display_course() = 0;
    
private:
    std::size_t id = 0;
    unsigned int classNum = 0;
    std::string name = "", college = "", password = "";
    vector <size_t> courseNum{};
};

class Student: public Person
{
public:
    virtual display_info() override;
    virtual display_course() override;
    bool enroll_course(size_t);
private:
};

class Teacher: public Person
{
public:
    virtual display_info() override;
    virtual display_course() override;
    bool enroll_course(size_t);
private:
};

#endif /* people_hpp */
