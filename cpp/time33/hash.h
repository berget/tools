/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  hash function
 *
 *        Version:  1.0
 *        Created:  07/10/2012 12:11:02 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#ifndef  HASH_INC
#define  HASH_INC

struct str_arg_t;

unsigned long time33_simple(const str_arg_t* arg);
unsigned long time33_simple_shift(const str_arg_t* arg);
unsigned long time33_simple_unsigned_char(const str_arg_t* arg);
unsigned long time33_simple_unsigned_long(const str_arg_t* arg);
unsigned long time33_simple_truncate(const str_arg_t* arg);
unsigned long time33_apache(const str_arg_t* arg);
unsigned long time33_php(const str_arg_t* arg);
unsigned long time33_simple_hybrid(const str_arg_t* arg);
unsigned long time33_debug(const str_arg_t* arg);

#endif   /* ----- #ifndef HASH_INC  ----- */
