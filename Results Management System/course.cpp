//
//  course.cpp
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
#include <map>
#include <utility>
#include <numeric>
#include <cmath>

#include "course.hpp"
#include "system.hpp"
#include "global.h"

using std::string;
using std::istream;
using std::pair;

istream& operator>>(istream &is, Course &c)
{
    using seq = Course::seq;
    using score = Course::score;
    
    is >> c.id >> c.name >> c.credit >> c.teacher;
    is.ignore();            //忽略\n
    
    string s;
    getline(is, s);
    std::stringstream record(s);
    while (!record.eof())
    {
        Student::seq x;
        score y;
        record >> x >> y;
        c.studentScore.insert(std::make_pair(x, y));
    }
    
    return is;
}

Require_course::~Require_course()
{
    using std::endl;
    
    if (id != 0)
    {
        static std::ofstream out_file("require_course.txt");
        out_file << id << ' ' << name << ' ' << credit << ' ' << teacher << endl;
        for (auto i = studentScore.begin(); i != studentScore.end(); i++)
            out_file << i->first << " " << i->second << " ";
        out_file << endl;
    }
    studentScore.clear();
}

double Require_course::get_gpa(const score& x) const
{
    using seq = Course::seq;
    using score = Course::score;
    
    score sum = std::accumulate(studentScore.begin(), studentScore.end(), 0,
                                [](const score &a, pair<seq, score> b){ return a + b.second; });
    return (double)studentScore.size() * x * get_credit() / sum;
}

Elective_course::~Elective_course()
{
    using std::endl;
    
    if (id != 0)
    {
        static std::ofstream out_file("elective_course.txt");
        out_file << id << ' ' << name << ' ' << credit << ' ' << teacher << endl;
        for (auto i = studentScore.begin(); i != studentScore.end(); i++)
            out_file << i->first << " " << i->second << " ";
        out_file << endl;
    }
    studentScore.clear();
}

double Elective_course::get_gpa(const score& x) const
{
    return sqrt((double)x) / 10 * get_credit();
}

bool Require_course::display(std::ostream &os, const int &x) const
{
    using std::endl;
    Result_system &system = Result_system::get_instance();
    
    if (x == NO_REQUIRED) return WRONG;
    else
    {
        os << get_id() << '\t' << get_name() << "\tRequired\t" << system.get_person(get_teacher())->get_name() << '\t' << get_credit();
        return OK;
    }
}

bool Elective_course::display(std::ostream &os, const int &x) const
{
    using std::endl;
    Result_system &system = Result_system::get_instance();
    
    os << get_id() << '\t' << get_name() << "\tElective\t" << system.get_person(get_teacher())->get_name() << '\t' << get_credit();
    return OK;
}

inline void Require_course::throw_student(const Person::seq &x)
{
    throw std::logic_error("You must attend a REQUIRED course.");
}

inline void Elective_course::throw_student(const Person::seq &x)
{
    auto stu_it = studentScore.find(x);
    if (stu_it == studentScore.end())
        throw std::logic_error("You are not in this class.");
    studentScore.erase(stu_it);
}

inline void Require_course::enroll_student(const Person::seq &x)
{
    throw std::invalid_argument("You cannot choose a REQUIRED course.");
}

inline void Elective_course::enroll_student(const Person::seq &x)
{
    auto stu_it = studentScore.find(x);
    if (stu_it != studentScore.end())
        throw std::invalid_argument("You have already been in this class.");
    studentScore.insert(std::make_pair(x, NO_GREADE));
}

void Course::print_score_table(std::ostream &os, const Score_mode &mode) const
{
    Result_system &system = Result_system::get_instance();
    std::vector <pair<seq, score> > myScore(studentScore.begin(), studentScore.end());
    
    if (mode == INCREASE_BY_SCORE)
        sort(myScore.begin(), myScore.end(), [](const pair<seq, score> &a, const pair<seq, score> &b)
             { return a.second < b.second; });
    else
        sort(myScore.begin(), myScore.end(), [](const pair<seq, score> &a, const pair<seq, score> &b)
             { return a.second > b.second; });
    
    for (auto u : myScore)
    {
        Person_ptr p = system.get_person(u.first);
        Student_ptr s = std::dynamic_pointer_cast<Student>(p);
        os << *s << u.second << std::endl;
    }
}