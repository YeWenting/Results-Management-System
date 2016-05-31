//
//  global.h
//  Results Management System
//
//  Created by YeWenting. on 16/5/29.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#ifndef global_h
#define global_h

#include "course.hpp"
#include <memory>

constexpr int OK = 1;
constexpr int WRONG = 0;
constexpr unsigned short int NO_GREADE = 65535;

typedef std::shared_ptr<Person> Person_ptr;
typedef std::shared_ptr<Student> Student_ptr;
typedef std::shared_ptr<Teacher> Teacher_ptr;
typedef std::shared_ptr<Course> Course_ptr;

#endif /* global_h */
