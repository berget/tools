/*
 * =====================================================================================
 *
 *       Filename:  benchmark.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/10/2012 12:05:54 CST
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

static long get_current_usec(void);

class Benchmark {
    public:
        Benchmark();
        ~Benchmark();

    public:
        void set_string(const string &str);
        void dump();

        void start();

    private:
        str_arg_t _str;
        vector<pair<string, time33_func_ptr> > _methods;
};


int main() {
    Benchmark* bench = new Benchmark();

    //bench->set_string("\x66\x66");
    bench->set_string("\xde\xad");
    bench->dump();

    bench->start();

    cout << "Done" << endl;

    delete bench;
    return 0;
}


Benchmark::Benchmark() {
    init_str_arg(&_str);
}

Benchmark::~Benchmark() {
}

void Benchmark::set_string(const string &str) {
    set_str_arg(&_str, str.c_str());
}

void Benchmark::dump() {
    dump_str_arg(&_str);
}

#define ADD_METHOD(m)   _methods.push_back(make_pair(#m, m));
void Benchmark::start() {
    cout << "start benchmark ..." << endl;

    ADD_METHOD(time33_simple);
    ADD_METHOD(time33_simple_shift);
    ADD_METHOD(time33_simple_unsigned_char);
    ADD_METHOD(time33_simple_truncate);
    ADD_METHOD(time33_apache);
    ADD_METHOD(time33_php);

    long begin_time = 0;
    long end_time = 0;
    double cost_time = 0;
    for (size_t i = 0; i < _methods.size(); ++i) {
        printf("- benchmark %s", _methods[i].first.c_str());
        time33_func_ptr time33_hash = _methods[i].second;
        begin_time = get_current_usec();

        for (size_t j = 0; j < BENCHMAKR_TIME; ++j) {
            time33_hash(&_str);
        }

        end_time = get_current_usec();
        cost_time = (end_time - begin_time) / (double)1000.0;
        printf(", cost %.2f ms\n", cost_time);
    }
}

long get_current_usec(void) {
    long result = 0;
    struct timeval tv;
    if (gettimeofday(&tv , NULL) == 0) {
        result = (tv.tv_sec * 1000000) + tv.tv_usec;
    }
    return result;
}
