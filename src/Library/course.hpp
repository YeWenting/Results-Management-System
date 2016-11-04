//
//  course.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef course_hpp
#define course_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "person.hpp"
#include "../Shared/global.hpp"

class Course
{
    friend std::istream& operator>>(std::istream&, Course&);
public:
    using seq = Shared::Course;
    using score = Shared::score;
    Course() = default;
    virtual ~Course() = default;
    virtual double get_gpa(const score&) const = 0;
    virtual void throw_student(const Shared::Person&) = 0;
    virtual void enroll_student(const Shared::Person&) = 0;
    const seq get_id() const { return id; };
    std::string get_name() const { return name; };
    Shared::Person get_teacher() const { return teacher; };
    score get_credit() const { return credit; };
    virtual bool display(std::ostream &os, const int &x = 0) const = 0;
    void print_score_table(std::ostream&, const Score_mode&) const;
    score get_score(const Shared::Person &x)
        {
            auto stu_it = studentScore.find(x);
            if (stu_it == studentScore.end())
                throw std::invalid_argument("The student is not exist.");
            return stu_it->second;
        }
    void change_score(const Shared::Person &x, const score &y)
        {
            auto stu_it = studentScore.find(x);
            if (stu_it == studentScore.end())
                throw std::invalid_argument("The student is not exist.");
            stu_it->second = y;
        }
    size_t get_student_num() const { return studentScore.size(); };
    bool in_course(const Shared::Person &x) const
        {
            auto stu_it = studentScore.find(x);
            if (stu_it == studentScore.end()) return 0;
            else return 1;
        }

protected:
    seq id = 0;
    std::string name;
    Shared::Person teacher;
    score credit = 0;
    std::map <seq, score> studentScore;
};

class Require_course : public Course
{
public:
    virtual ~Require_course();
    virtual double get_gpa(const score&) const override final;
    virtual void throw_student(const Shared::Person&) override final;
    virtual void enroll_student(const Shared::Person&) override final;
    virtual bool display(std::ostream &os, const int &x = 0) const override final;
};

class Elective_course : public Course
{
public:
    virtual ~Elective_course();
    virtual double get_gpa(const score&) const override final;
    virtual void throw_student(const Shared::Person&) override final;
    virtual void enroll_student(const Shared::Person&) override final;
    virtual bool display(std::ostream &os, const int &x = 0) const override final;
};

#endif /* course_hpp */
