//
//  global.hpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef global_h
#define global_h

#include <memory>
#include <stdexcept>

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

typedef unsigned short int Score_mode;

constexpr int RIGHT = 1;
constexpr int WRONG = 0;
constexpr unsigned short int NO_GREADE = 0;
constexpr unsigned char NO_REQUIRED = 1;
constexpr unsigned short int MAX_SCORE = 100;
constexpr unsigned short int MIN_SCORE = 0;
constexpr Score_mode INCREASE_BY_SCORE = 0;
constexpr Score_mode DECREASE_BY_SCORE = 1;

bool process_error(std::invalid_argument);

#endif /* global_h */
