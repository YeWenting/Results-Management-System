//
//  system.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef system_hpp
#define system_hpp

#include <stdio.h>
#include <map>
#include <memory>

#include "person.hpp"
#include "course.hpp"
#include "global.h"

class Result_system
{
private:
    Result_system();
    static std::unique_ptr<Result_system> m_instance;

public:
    static Result_system& get_instance()      //必须加引用
    {
        if (m_instance == nullptr)
            m_instance.reset(new Result_system);
        return *m_instance;
    }
    
public:
    Person_ptr get_person(const Person::seq &);
    Course_ptr get_course(const Course::seq &);
private:
    std::map <Person::seq, Person_ptr> num_to_person;
    std::map <Course::seq, Course_ptr> num_to_course;
};

//添加课程记得判断存不存在
//显示某课程的学生 并且记得判断老师是否正确

#endif /* system_hpp */
