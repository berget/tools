/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  test only
 *
 *        Version:  1.0
 *        Created:  07/10/2012 15:16:52 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sys/time.h>

#include "common.h"
#include "hash.h"

using namespace std;

#define DP(m)       #m << "=" << m << ","
#define DP_SIZE(m)  #m << "=" << sizeof(m) << ","

int main() {
    cout << DP(sizeof(int)) << endl;
    cout << DP(sizeof(unsigned int)) << endl;
    cout << DP(sizeof(unsigned long int)) << endl;
    cout << DP(sizeof(int32_t)) << endl;
    cout << DP(sizeof(int64_t)) << endl;
    cout << DP(sizeof(uint32_t)) << endl;
    cout << DP(sizeof(uint64_t)) << endl;
    cout << DP(sizeof(long long)) << endl;
    cout << DP(sizeof(long)) << endl;
    cout << DP(sizeof(unsigned long)) << endl;
    return 0;
}
