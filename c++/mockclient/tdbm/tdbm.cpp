/*
 * =====================================================================================
 *
 *       Filename:  tdbm.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2011 00:58:47 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "tdbm.h"

TDBM* tdbm_open(const char* path, int a, int b, int c, int d) {
    TDBM* result = new TDBM;
    return result;
}

datum tdbm_fetch_r(TDBM* db, datum) {
    datum d;
    return d;
}

int tdbm_store_r(TDBM* db, datum k, datum v, int a) {
    return 0;
}

void tdbm_close(TDBM* db) {
}

void tdbm_truncate(TDBM* db) {
}
