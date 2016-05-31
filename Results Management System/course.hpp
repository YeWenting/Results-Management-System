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

class Course
{
    friend std::istream& operator>>(std::istream&, Course&);
public:
    typedef size_t seq;
    typedef unsigned short score;
    Course() = default;
    Course &display(std::ostream &os)
        { do_display(os); return *this; };
    const Course &display(std::ostream &os) const
        { do_display(os); return *this; };
    virtual double get_gpa(const score&) const = 0;
    virtual void throw_student(const Person::seq&) = 0;
    virtual void enroll_student(const Person::seq&) = 0;
    seq get_id() const { return id; };
    std::string get_name() const { return name; };
private:
    seq id = 0;
    std::string name;
    Person::seq teacher;
    virtual void do_display(std::ostream &os) const = 0;
    
protected:
    score credit = 0;
    std::map <seq, score> studentScore;
};

class Require_course : public Course
{
public:
    virtual double get_gpa(const score&) const override final;
    virtual void throw_student(const Person::seq&) override final;
    virtual void enroll_student(const Person::seq&) override final;
private:
    virtual void do_display(std::ostream &os) const override final;
};

class Elective_course : public Course
{
public:
    virtual double get_gpa(const score&) const override final;
    virtual void throw_student(const Person::seq&) override final;
    virtual void enroll_student(const Person::seq&) override final;
private:
    virtual void do_display(std::ostream &os) const override final;
};

#endif /* course_hpp */
