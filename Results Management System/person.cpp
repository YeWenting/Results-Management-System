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

bool Person::authorize(const std::string &s)
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

std::ostream& operator<<(std::ostream &os, const Student &s)
{
    os << s.name << '\t' << s.id << '\t' << s.college << '\t' << s.classNum << '\t';
    return os;
}

std::ostream& operator<<(std::ostream &os, const Teacher &t)
{
    os << t.name << '\t' << t.id << '\t' << t.college << '\t';
    return os;
}

void Student::enroll_course()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Result_system &system = Result_system::get_instance();
    Course::seq courseNum;
    
    //用课程的信息进行验证 考虑课程信息保存在远端 防止用户欺骗
    cout << "Please input the course ID\n" <<endl;
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
            cin.clear();
            cin >> c;
            if (!cin || c == 'n') break;
            cout << "Please input the course ID\n" <<endl;
            continue;
        }
    }
}

const Person& Student::display_info(std::ostream &os)
{
    using std::endl;
    os << "\n\nHello student " << name << ", here is your basic info:)\nID: " << id << "\nClass: " << classNum << "\nCollege: " << college << "\nCourses to attend: " << endl;
    
    Result_system &system = Result_system::get_instance();
    for (auto u : course)
    {
        Course_ptr myCourse = system.get_course(u);
        myCourse->display(os);
        os << '\t' << myCourse->get_gpa(myCourse->get_score(this->id)) << '\t' << myCourse->get_score(this->id) << endl;
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
    
    os << "\n\nDear Porf." << name << ", here is your basic info:)\nID: " << id << "\nCollege: " << college << "\nCourses to teach: " << endl;
    
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


//给课程 给student 给分数
void Teacher::modify_score(std::istream &is, std::ostream &os)
{
    using std::endl;
    Course::seq course = 0;
    Person::seq student = 0;
    Course::score  newScore = 0;
    Result_system & system = Result_system::get_instance();
    
    os << "Please input the course ID, student ID, and new score:" << endl;
    while (is >> course >> student >> newScore)
    {
        try
        {
            Course_ptr myCourse = system.get_course(course);
            
            if (newScore > MAX_SCORE || !is.good())
                throw std::invalid_argument("Input is incorrect!");
            
            //判断授课老师是此人吗
            auto course_it = find(this->course.begin(), this->course.end(), myCourse->get_id());
            if (course_it == this->course.end())
                throw std::invalid_argument("You do not teach this class");
            
            //修改分数
            myCourse->change_score(student, newScore);
            os << "Change Successfully\nNew score table is:\n" << endl;
            myCourse->print_score_table(std::cout);
            break;
        }
        catch (std::invalid_argument err)
        {
            os << err.what() << "\nTry again? Enter y or n" <<endl;
            char c;
            is.clear();
            is >> c;
            if (!is || c == 'n') break;
            os << "Please input the course ID, student ID, and new score:" << endl;
            continue;
        }
    }
}

void Teacher::check_score(std::istream &is, std::ostream &os) const
{
    using std::endl;
    Result_system & system = Result_system::get_instance();
    
    os << "Please enter the course ID" <<endl;
    Course::seq x;
    while(is >> x)
    {
        try
        {
            Course_ptr printCourse = system.get_course(x);
            if (printCourse->get_teacher() != this->id)
                throw std::invalid_argument("You do not teach this class");
            printCourse->print_score_table(os);
            break;
        }
        catch (std::invalid_argument err)
        {
            os << err.what() << "\nTry again? Enter y or n" <<endl;
            char c;
            is.clear();
            is >> c;
            if (!is || c == 'n') break;
            os << "Please input the course ID, student ID, and new score:" << endl;
            continue;
        }
    }
}







