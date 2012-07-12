/*
 * =====================================================================================
 *
 *       Filename:  lconvert.cpp
 *
 *    Description:  convert str into hash code
 *
 *        Version:  1.0
 *        Created:  07/11/2012 00:46:41 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include <stdio.h>

#include <iostream>

#include "common.h"
#include "hash.h"

using namespace std;

int main() {
    string line;
    unsigned long hash_code = 0;
    str_arg_t str;
    init_str_arg(&str);
    while (cin >> line) {
        set_str_arg(&str, line.c_str());
        hash_code = time33_simple_unsigned_char(&str);
        cout << line << " " << hash_code << endl;
    }
    return 0;
}
