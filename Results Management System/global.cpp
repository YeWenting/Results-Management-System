//
//  global.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/1.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//

#include <stdio.h>
#include <stdexcept>
#include <iostream>

#include "global.h"

void process_error(std::invalid_argument err, std::istream &is, std::ostream &os)
{
    using std::cout;
    using std::endl;
    using std::cin;
    
    cout << err.what() << "\nTry again? Enter y or n" <<endl;
    char c;
    cin >> c;
    if (!cin || c == 'n') break;
    continue;
}
