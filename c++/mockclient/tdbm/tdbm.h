/*
 * =====================================================================================
 * 
 *       Filename:  tdbm.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  10/08/2011 00:58:44 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 * 
 * =====================================================================================
 */

#ifndef  TDBM_INC
#define  TDBM_INC

enum {
    TDBM_REPLACE = 0,
};

typedef struct {
    int a;
} TDBM;


typedef struct {
    char* dptr;
    unsigned int dsize;
} datum;

TDBM* tdbm_open(const char* path, int a, int b, int c, int d);

datum tdbm_fetch_r(TDBM* db, datum);

void tdbm_close(TDBM* db);
void tdbm_truncate(TDBM* db);

int tdbm_store_r(TDBM* db, datum k, datum v, int a);

#endif   /* ----- #ifndef TDBM_INC  ----- */
