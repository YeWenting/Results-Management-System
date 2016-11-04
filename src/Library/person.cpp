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
#include <algorithm>

#include "person.hpp"
#include "../Shared/global.hpp"
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
    is.ignore();            //ignore the \n
    
    string s;
    getline(is, s);
    std::stringstream record(s);
    std::istream_iterator<Shared::Course> in_iter(record), eof;
    p.course = vector<Shared::Course> (in_iter, eof);
    
    return is;
}

std::istream &operator>> (std::istream &is, Teacher &p)
{
    
    is >> p.id >> p.password >> p.name >> p.college;
    is.ignore();            //ignore the \n
    
    string s;
    getline(is, s);
    std::stringstream record(s);
    std::istream_iterator<Shared::Course> in_iter(record), eof;
    p.course = vector<Shared::Course> (in_iter, eof);
    
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
/*
  store the data to the "student.txt" and destory the student
*/
Student::~Student()
{
    using std::endl;
    
    if (id != 0)
    {
        static std::ofstream out_file("student.txt");
        out_file << id << ' ' << password << ' ' << name
            << ' '  << college << ' ' << classNum << endl;
        copy(course.begin(), course.end(), std::ostream_iterator<int>(out_file, " "));
        out_file << endl;
    }
    course.clear();
}

std::string Student::enroll_course(Shared::Course courseNum)
{
    Result_system &system = Result_system::get_instance();
    
    Course_ptr enrollCourse = system.get_course(courseNum);
    enrollCourse->enroll_student(get_id());
    course.push_back(enrollCourse->get_id());
    return enrollCourse->get_name();
}

std::string Student::cancel_course(Shared::Course courseNum)
{
    Result_system &system = Result_system::get_instance();
    Course_ptr cancelCourse = system.get_course(courseNum);
    
    cancelCourse->throw_student(get_id());
    course.erase(find(course.begin(), course.end(), courseNum));
    return cancelCourse->get_name();
}

const Person& Student::display_info(std::ostream &os, const Score_mode &mode)
{
    using std::endl;
    os << "\n\nHello student " << name << ", here is your basic info:)\nName: " <<
        name << "\nID: " << id << "\nClass: " << classNum << "\nCollege: "
        << college << "\nCourses to attend: " << endl;
    
    Result_system &system = Result_system::get_instance();
    //输出基本信息
    if (mode == INCREASE_BY_SCORE)
        sort(course.begin(), course.end(), [&system, this](const Shared::Course &a, const Shared::Course &b)
             { return system.get_course(a)->get_score(this->id) < system.get_course(b)->get_score(this->id); });
    else
        sort(course.begin(), course.end(), [&system, this](const Shared::Course &a, const Shared::Course &b)
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
/*
  store the data to the "teacher.txt" and destory the teacher
*/
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
/*
  display the teacher's basic info
*/
const Person& Teacher::display_info(std::ostream &os, const Score_mode &mode)
{
    using std::endl;
    
    os << "\n\nDear Porf." << name << ", here is your basic info:)\nID: "
        << id << "\nCollege: " << college << "\nCourses to teach: " << endl;
    
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

void Teacher::modify_score(std::ostream &os, Shared::Course course,
                           seq student, Shared::score newScore)
{
    Result_system &system = Result_system::get_instance();
    Course_ptr myCourse = system.get_course(course);
    
    /* Check the authorization */
    auto course_it = find(this->course.begin(), this->course.end(), myCourse->get_id());
    if (course_it == this->course.end())
        throw std::invalid_argument("You do not teach this class");
    
    /* Modify the score */
    myCourse->change_score(student, newScore);
    os << "\nChange Successfully!\nNew score table is:\n" << std::endl;
    myCourse->print_score_table(os, INCREASE_BY_SCORE);
}

void Teacher::check_score(Shared::Course courseNum, std::ostream &os, const Score_mode &mode) const
{
    Result_system &system = Result_system::get_instance();
    
    Course_ptr printCourse = system.get_course(courseNum);
    if (printCourse->get_teacher() != this->id)
        throw std::invalid_argument("You do not teach this class");
    printCourse->print_score_table(os, mode);
}
