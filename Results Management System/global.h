//
//  global.h
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef global_h
#define global_h

#include <memory>

constexpr int OK = 1;
constexpr int WRONG = 0;
constexpr unsigned short int NO_GREADE = 65535;
constexpr unsigned char NO_REQUIRED = 1;

class Person;
class Student;
class Teacher;
class Course;
class Elective_course;
class Result_system;

typedef std::shared_ptr<Person> Person_ptr;
typedef std::shared_ptr<Student> Student_ptr;
typedef std::shared_ptr<Teacher> Teacher_ptr;
typedef std::shared_ptr<Course> Course_ptr;
typedef std::shared_ptr<Elective_course> Elective_ptr;
typedef std::shared_ptr<Result_system> System_ptr;

#endif /* global_h */
