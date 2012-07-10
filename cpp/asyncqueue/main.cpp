/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/2011 13:45:34 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include <iostream>
#include "asyncqueue.h"
using namespace std;

#ifndef DP
#define DP(m) #m << "=" << m << ","
#endif

int main() {
    AsyncQueue q(3);
    if (!q.init()) {
        cerr << "Failed to init AsyncQueue" << endl;
        return 1;
    }

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    int *p;

    cout << "push: " << DP(num1) << endl;
    q.push(&num1);
    cout << "push: " << DP(num2) << endl;
    q.push(&num2);
    cout << "push: " << DP(num3) << endl;
    q.push(&num3);

    cout << "pop" << endl;
    p = (int*)q.pop();
    cout << DP(*p) << endl;

    cout << "Done" << endl;
    return 0;
}
