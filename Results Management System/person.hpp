//
//  people.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef people_hpp
#define people_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "global.h"

class Student;
class Teacher;

class Person
{
public:
    typedef size_t seq ;
    Person() = default;
    Person(const seq& i, const std::string &n, const std::string &cl, std::vector <seq> &co, const std::string &pa):
        id(i), name(n), college(cl), course(co), password(pa) {};
    virtual ~Person() = default;
    seq get_id() const { return id; };
    std::string get_name() { return name; };
    
    bool authorize(const std::string &);
    virtual const Person &display_info(std::ostream&, const Score_mode&) = 0;
protected:
    seq id = 0;
    std::string name, college, password;
    std::vector <seq> course;
};


class Student: public Person
{
friend std::istream &operator>>(std::istream&, Student&);
friend std::ostream& operator<<(std::ostream&, const Student&);
    
public:
    Student() = default;
    virtual ~Student();
    
    virtual const Person &display_info(std::ostream&, const Score_mode&) override final;
    void enroll_course();
    void cancel_course();
    const Person& display_course(std::ostream&) const;
private:
    unsigned int classNum = 0;
};


class Teacher: public Person
{
friend std::istream &operator>>(std::istream&, Teacher&);
friend std::ostream& operator<<(std::ostream&, const Teacher&);
    
public:
    Teacher() = default;
    virtual ~Teacher();
    virtual const Person &display_info(std::ostream&, const Score_mode&) override final;
//    virtual void storage() override final;
    void modify_score(std::istream &, std::ostream &);  //course student score
    void check_score(std::istream &, std::ostream &, const Score_mode&) const;
};

#endif /* people_hpp */


