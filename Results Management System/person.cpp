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
#include <iterator>
#include <curses.h>

#include "person.hpp"
#include "global.hpp"
#include "course.hpp"
#include "system.hpp"

using std::string;
using std::vector;

bool Person::authorize(const std::string &s)
{
    if (s != password) return WRONG;
    else return RIGHT;
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

Student::~Student()
{
    using std::endl;
    
    if (id != 0)
    {
        static std::ofstream out_file("student.txt");
        out_file << id << ' ' << password << ' ' << name << ' '  << college << ' ' << classNum << endl;
        copy(course.begin(), course.end(), std::ostream_iterator<int>(out_file, " "));
        out_file << endl;
    }
    course.clear();
}

void Student::enroll_course()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Result_system &system = Result_system::get_instance();
    Course::seq courseNum;
    
    while (true)
    {
        try
        {
            cout << "Please input the course ID" <<endl;
            cin >> courseNum;
            Course_ptr enrollCourse = system.get_course(courseNum);
            enrollCourse->enroll_student(get_id());
            course.push_back(enrollCourse->get_id());
            cout << "You attend the " << enrollCourse->get_name() << " course successfully." << endl;
            break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

void Student::cancel_course()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Result_system &system = Result_system::get_instance();
    Course::seq courseNum;
    
    
    while (true)
    {
        try
        {
            cout << "Please input the course ID\n" <<endl;
            cin >> courseNum;
            auto course_it = find(course.begin(), course.end(), courseNum);
            if (course_it == course.end())
                throw std::invalid_argument("You are not attending this class!");
            
            Course_ptr cancelCourse = system.get_course(courseNum);
            cancelCourse->throw_student(get_id());
            course.erase(course_it);
            cout << "You cancel the " << cancelCourse->get_name() << " course successfully." << endl;
            break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

const Person& Student::display_info(std::ostream &os, const Score_mode &mode)
{
    using std::endl;
    system("clear");
    os << "\n\nHello student " << name << ", here is your basic info:)\nName: " << name << "\nID: " << id << "\nClass: " << classNum << "\nCollege: " << college << "\nCourses to attend: " << endl;
    
    Result_system &system = Result_system::get_instance();
    //输出基本信息
    if (mode == INCREASE_BY_SCORE)
        sort(course.begin(), course.end(), [&system, this](const seq &a, const seq &b)
             { return system.get_course(a)->get_score(this->id) < system.get_course(b)->get_score(this->id); });
    else
        sort(course.begin(), course.end(), [&system, this](const seq &a, const seq &b)
             { return system.get_course(a)->get_score(this->id) > system.get_course(b)->get_score(this->id); });
    
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

Teacher::~Teacher()
{
    using std::endl;
    
    if (id != 0)
    {
        static std::ofstream out_file("teacher.txt");
        out_file << id << ' ' << password << ' ' << name << ' '  << college << endl;
        copy(course.begin(), course.end(), std::ostream_iterator<int>(out_file, " "));
        out_file << endl;
    }
    course.clear();
}

const Person& Teacher::display_info(std::ostream &os, const Score_mode &mode)
{
    using std::endl;
    
    system("clear");
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
    
    while (true)
    {
        try
        {
            os << "Please input the course ID, student ID, and new score:" << endl;
            is >> course >> student >> newScore;
            //找课
            Course_ptr myCourse = system.get_course(course);
            if (newScore > MAX_SCORE || !is.good())
                throw std::invalid_argument("Input is incorrect!");
            //判断授课老师是此人吗
            auto course_it = find(this->course.begin(), this->course.end(), myCourse->get_id());
            if (course_it == this->course.end())
                throw std::invalid_argument("You do not teach this class");
            //修改分数
            myCourse->change_score(student, newScore);
            os << "\nChange Successfully!\nNew score table is:\n" << endl;
            myCourse->print_score_table(std::cout, INCREASE_BY_SCORE);
            break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}

void Teacher::check_score(std::istream &is, std::ostream &os, const Score_mode &mode) const
{
    using std::endl;
    Result_system & system = Result_system::get_instance();
    
    Course::seq x;
    while(true)
    {
        try
        {
            os << "Please enter the course ID" <<endl;
            is >> x;
            Course_ptr printCourse = system.get_course(x);
            if (printCourse->get_teacher() != this->id)
                throw std::invalid_argument("You do not teach this class");
            printCourse->print_score_table(os, mode);
            break;
        }
        catch (std::invalid_argument err)
        {
            if (!process_error(err)) break;
        }
    }
}







