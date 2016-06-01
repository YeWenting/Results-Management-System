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

const Person& Student::display_info(std::ostream &os)
{
    using std::endl;
    os << "Hello student " << name << ", here is your basic info:)\nID: " << id << "\nClass: " << classNum << "\nCollege: " << college << "\nCourses to attend: " << endl;
    
    Result_system &system = Result_system::get_instance();
    for (auto u : course)
    {
        Course_ptr myCourse = system.get_course(u);
        myCourse->display(os);
        os << '\t' << myCourse->get_score(this->id) << endl;
    }
    os << endl;
    return *this;
}

const Person& Student::display_course(std::ostream &os) const
{
    Result_system &system = Result_system::get_instance();
    
    system.print_available_course(*this, std::cout);
    return *this;
}

const Person& Teacher::display_info(std::ostream &os)
{
    using std::endl;
    
    os << "Dear Porf." << name << ", here is your basic info:)\nID: " << id << "\nCollege: " << college << "\nCourses to teach: " << endl;
    
    Result_system & system = Result_system::get_instance();
    for (auto u : course)
    {
        Course_ptr myCourse = system.get_course(u);
        myCourse->display(os);
        os << '\t' << myCourse->get_student_num() << endl;
    }
    os << endl;
    return *this;
}

//bool Teacher::modify_score(const seq &course, const seq &student, const unsigned int &score)
//{
//    
//}