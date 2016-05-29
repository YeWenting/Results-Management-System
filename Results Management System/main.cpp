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

using namespace std;

class A
{
public:
    A(){value = 0; }
    ~A(){cout<<"kobe"<<endl;}

private:
    int value;
};

void fuck()
{
//    A *pA = new A;
//    return;
}

int main(int argc, const char * argv[])
{
    // insert code here...
//    fuck();
//    A a;
    vector <vector <int> > a(0);
    a = vector<vector<int> > (3, vector<int>(4));

    
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
