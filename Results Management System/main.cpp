//
//  main.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/5/28.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "system.hpp"

void fuck()
{
//    A *pA = new A;
//    return;
}

using std::unique_ptr;

int main(int argc, const char * argv[])
{
    std::shared_ptr<Result_system> system = Result_system::get_instance();
    
//    unsigned char status = 0;
//    while (OK)
//    {
//        unsigned short input;
//        std::cin >> input
//        switch (status) of
//        {
//        case 0:
//            
//        }
//    }
//    Person_ptr p1 = system.get_person(2001007);
//    Teacher_ptr t = std::dynamic_pointer_cast<Teacher>(p1);
////    s->enroll_course();
//    t->display_info(std::cout);
    
    Person_ptr p2 = system->get_person(2014211519);
    Student_ptr s = std::dynamic_pointer_cast<Student>(p2);
    s->display_info(std::cout);
    s->display_course(std::cout);
    
    
//    int x;
//    char ch;
//    using std::cin;
//    std::cin >> x;
//    std::cin.ignore();
//    cin >> ch;
//    std::cout << ch << std::endl;
    return 0;
}
