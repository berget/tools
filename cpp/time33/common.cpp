/*
 * =====================================================================================
 *
 *       Filename:  common.cpp
 *
 *    Description:  common method
 *
 *        Version:  1.0
 *        Created:  07/10/2012 13:46:16 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#include "common.h"

void init_str_arg(str_arg_t* arg) {
    arg->length = 0;
    arg->str    = NULL;
    arg->ustr   = NULL;
}

void set_str_arg(str_arg_t* arg, const char* str) {
    if (arg->str != NULL) {
        delete arg->str;
        arg->str = NULL;
    }
    if (arg->ustr != NULL) {
        delete arg->ustr;
        arg->ustr = NULL;
    }

    arg->length = strlen(str);
    arg->str = new char[arg->length+1];
    arg->ustr = new unsigned char[arg->length+1];

    memset(arg->str, 0, arg->length+1);
    memset(arg->ustr, 0, arg->length+1);

    memcpy(arg->str, str, arg->length);
    memcpy(arg->ustr, str, arg->length);
}

void dump_str_arg(str_arg_t* arg) {
    printf("================================================================\n");
    printf("dump str_arg_t: %p\n", arg);
    printf("length = %d\n", arg->length);

    printf("str = %s\n", arg->str);
    printf("str(hex) = \"");
    for (int i = 0; i < arg->length; ++i) {
        const char &c = arg->str[i];
        printf("\\x%x", c&0xff);
    }
    printf("\"\n");

    printf("ustr = %s\n", arg->ustr);
    printf("ustr(hex) = \"");
    for (int i = 0; i < arg->length; ++i) {
        const unsigned char &c = arg->str[i];
        printf("\\x%x", c&0xff);
    }
    printf("\"\n");
    printf("================================================================\n");
}
