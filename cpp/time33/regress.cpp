/*
 * =====================================================================================
 *
 *       Filename:  regress.cpp
 *
 *    Description:  regression testing
 *
 *        Version:  1.0
 *        Created:  07/10/2012 14:26:50 CST
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

typedef unsigned long (*time33_func_ptr)(const str_arg_t* arg);

class Regression {
    public:
        Regression();
        ~Regression();

    public:
        void add_case(const string &str, unsigned long hash_code);

        void start();

    private:
        vector<pair<str_arg_t*, unsigned long> > _cases;
        vector<pair<string, time33_func_ptr> > _methods;
};

int main() {
    Regression* regress = new Regression();

    regress->add_case("", 5381L);
    regress->add_case("0", 177621L);
    regress->add_case("01", 5861542L);
    regress->add_case("\xde\xad", 5867408L);
    regress->add_case("清人", 6958613525280L);
    regress->add_case("病人", 6958613525280L);
    regress->add_case("清", 193633672L);
    regress->add_case("病", 193633672L);
    //regress->add_case("\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad", 17580474771702234258L),
    //regress->add_case("\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad\xde\xad", 19129416775443036769L),

    regress->start();

    cout << "Done" << endl;

    delete regress;
    return 0;
}

Regression::Regression() {
}

Regression::~Regression() {
}

void Regression::add_case(const string &str, unsigned long hash_code) {
    str_arg_t* str_arg = new str_arg_t;

    init_str_arg(str_arg);
    set_str_arg(str_arg, str.c_str());

    _cases.push_back(make_pair(str_arg, hash_code));
}

#define ADD_METHOD(m) _methods.push_back(make_pair(#m, m));
void Regression::start() {
    ADD_METHOD(time33_simple);
    ADD_METHOD(time33_simple_shift);
    ADD_METHOD(time33_simple_unsigned_char);
    ADD_METHOD(time33_simple_unsigned_long);
    ADD_METHOD(time33_simple_truncate);
    ADD_METHOD(time33_apache);
    ADD_METHOD(time33_php);
    ADD_METHOD(time33_debug);

    string name;
    for (size_t i = 0; i < _cases.size(); ++i) {
        const str_arg_t* str = _cases[i].first;
        const unsigned long hash_code = _cases[i].second;

        printf("#%d str = \"%s\", \"", (int)i, str->str);
        for (int k = 0; k < str->length; ++k) {
            const char &c = str->str[k];
            printf("\\x%x", c&0xff);
        }

        printf("\", \"");
        for (int k = 0; k < str->length; ++k) {
            const char &c = str->str[k];
            if (k > 0)
                printf(" ");
            printf("%u", c&0xff);
        }

        printf("\"\n");

        for (size_t j = 0; j < _methods.size(); ++j) {
            name = _methods[j].first;
            time33_func_ptr time33_hash = _methods[j].second;

            printf("   - %s, ", name.c_str());
            unsigned long actual = time33_hash(str);
            printf("[actual]: %lu, ", actual);
            printf("[expect]: %lu, ", hash_code);
            printf("%s", (hash_code == actual) ? "\033[1;32mOK.\033[0;0m": "\033[1;31mFailed!\033[0;0m");
            printf("\n");
        }
    }
}
