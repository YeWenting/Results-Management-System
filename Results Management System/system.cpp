//
//  system.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <iterator>
#include <iostream>

#include "system.hpp"
#include "person.hpp"
#include "course.hpp"
#include "global.h"

using std::string;
using std::ifstream;
using std::istream_iterator;
using std::shared_ptr;

std::unique_ptr<Result_system> Result_system::m_instance = nullptr;

Result_system::Result_system()
{
    ifstream stu_file("student.txt"), tea_file("teacher.txt"), require_file("require_course.txt"), elective_file("elective_course.txt");
    
    while (!stu_file.eof())
    {
        auto temp = std::make_shared<Student>();
        stu_file >> *temp;
        num_to_person.insert(make_pair(temp->get_id(), temp));
    }
    
    while (!tea_file.eof())
    {
        auto temp = std::make_shared<Teacher>();
        tea_file >> *temp;
        num_to_person.insert(make_pair(temp->get_id(), temp));
    }
    
    //teacher 多了一个
//    std::cout << "haha" << std::endl;
//    for (auto i = num_to_person.begin(); i != num_to_person.end(); ++i)
//    {
//        std::cout << i->first << ' ' << i->second->get_name() << std::endl;
//    }
    
    while (!require_file.eof())
    {
        auto temp = std::make_shared<Require_course>();
        require_file >> *temp;
        num_to_course.insert(make_pair(temp->get_id(), temp));
    }
    
    while (!elective_file.eof())
    {
        auto temp = std::make_shared<Elective_course>();
        elective_file >> *temp;
        num_to_course.insert(make_pair(temp->get_id(), temp));
    }
}

//inline Result_system::Garbo::~Garbo()
//{
//    
//}

Person_ptr Result_system::get_person(const Person::seq &personID)
{
    auto person_it = num_to_person.find(personID);
    if (person_it == num_to_person.end())
        throw std::invalid_argument("Your id/password is incorrect.");
    return person_it->second;
}

Course_ptr Result_system::get_course(const Course::seq &num)
{
    auto course_it = num_to_course.find(num);
    if (course_it == num_to_course.end())
        throw std::invalid_argument("The course id is incorrect.");
    return course_it->second;
}