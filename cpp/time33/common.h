/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  common for time33 hash function
 *
 *        Version:  1.0
 *        Created:  07/10/2012 12:07:23 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#ifndef  COMMON_INC
#define  COMMON_INC

#include <stdlib.h>

const unsigned long HASH_START_VALUE = 5381;
const size_t BENCHMAKR_TIME = 1000L * 1000 * 10 * 10;

struct str_arg_t {
    char* str;
    unsigned char* ustr;
    int length;
};

void init_str_arg(str_arg_t* arg);

void set_str_arg(str_arg_t* arg, const char* str);

void dump_str_arg(str_arg_t* arg);

#endif   /* ----- #ifndef COMMON_INC  ----- */
