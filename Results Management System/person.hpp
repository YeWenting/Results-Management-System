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

class Student;
class Teacher;

class Person
{
friend std::istream &operator>>(std::istream&, Student&);
friend std::istream &operator>>(std::istream&, Teacher&);

public:
    typedef size_t seq ;
    Person() = default;
    Person(const seq& i, const std::string &n, const std::string &cl, std::vector <seq> &co, const std::string &pa):
        id(i), name(n), college(cl), course(co), password(pa) {};
    ~Person() = default;
    virtual const Person &display_info() = 0;
    virtual const Person &display_course() = 0;
    bool authorize(const std::string &);
    seq get_id() { return id; };
    std::string get_name() { return name; };        //For debug
    
private:
    seq id = 0;
    std::string name, college, password;

protected:
    std::vector <seq> course;
};


class Student: public Person
{
friend std::istream &operator>>(std::istream&, Student&);
    
public:
    Student() = default;
    virtual const Person &display_info() override final;
    virtual const Person &display_course() override final;
    void enroll_course();
    void cancel_course();
    
private:
    unsigned int classNum = 0;
};


class Teacher: public Person
{
friend std::istream &operator>>(std::istream&, Teacher&);
    
public:
    Teacher() = default;
    virtual const Person &display_info() override final;
    virtual const Person &display_course() override final;
    bool modify_score(const seq &, const seq &, const unsigned int &);  //course student score
    
};



#endif /* people_hpp */


