//
//  people.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <string>

#include "person.hpp"
#include "global.h"
#include "course.hpp"
#include "system.hpp"

using std::string;
using std::vector;

inline bool Person::authorize(const std::string &s)
{
    if (s != password) return WRONG;
    else return OK;
}

std::istream &operator>> (std::istream &is, Student &p)
{
    
    is >> p.id >> p.password >> p.name >> p.college >> p.classNum;
    is.ignore();            //忽略\n
    
    string s;
    getline(is, s);
    std::stringstream record(s);
    std::istream_iterator<Person::seq> in_iter(record), eof;
    std::cout << s << std::endl;
    p.course = vector<Person::seq> (in_iter, eof);
    
    //判断输入是否成功
    
    return is;
}

std::istream &operator>> (std::istream &is, Teacher &p)
{
    
    is >> p.id >> p.password >> p.name >> p.college;
    is.ignore();            //忽略\n
    
    string s;
    getline(is, s);
    std::stringstream record(s);
    std::istream_iterator<Person::seq> in_iter(record), eof;
    std::cout << s << std::endl;
    p.course = vector<Person::seq> (in_iter, eof);
    
    //判断输入是否成功
    
    return is;
}

void Student::enroll_course()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Result_system &system = Result_system::get_instance();
    Course::seq courseNum;
    
    //用课程的信息进行验证 考虑课程信息保存在远端 防止用户欺骗
    while (cin >> courseNum)
    {
        try
        {
            Course_ptr enrollCourse = system.get_course(courseNum);
            enrollCourse->enroll_student(get_id());
            course.push_back(enrollCourse->get_id());
            cout << "You attend the " << enrollCourse->get_name() << " course successfully." << endl;
            break;
        }
        catch (std::invalid_argument err)
        {
            cout << err.what() << "\nTry again? Enter y or n" <<endl;
            char c;
            cin >> c;
            if (!cin || c == 'n') break;
            continue;
        }
    }
}

const Person& Student::display_info()
{
    
    return *this;
}

const Person& Student::display_course()
{
    
    return *this;
}

const Person& Teacher::display_info()
{
    
    return *this;
}

const Person& Teacher::display_course()
{
    
    return *this;
}


//Course_ptr enrollCourse = system.get_course(courseNum);
//try
//{
//    enrollCourse->throw_student(get_id());
//}
//catch (std::logic_error err)
//{
//    cout << err.what() << "\nTry again? Enter y or n" <<endl;
//    char c;
//    cin >> c;
//    if (!cin || c == 'n') break;
//    }
//    course.erase(find(course.begin(), course.end(), courseNum));