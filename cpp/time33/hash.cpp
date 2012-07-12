/*
 * =====================================================================================
 *
 *       Filename:  hash.cpp
 *
 *    Description:  hash function
 *
 *        Version:  1.0
 *        Created:  07/10/2012 12:11:25 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include "hash.h"

#include "common.h"

using namespace std;

static const unsigned long TIME_FACTOR = 33;

unsigned long time33_simple_hybrid(const str_arg_t* arg) {
    unsigned int hash1 = HASH_START_VALUE;
    unsigned int hash2 = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash1 = hash1 * 33 + (unsigned char)arg->str[i];
        hash2 = hash2 * 31 + (unsigned char)arg->str[i];
    }
    return (((unsigned long)hash1 << 32L) | (unsigned long)hash2);
}

unsigned long time33_simple(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = hash * TIME_FACTOR + (unsigned long)arg->str[i];
    }
    return hash;
}

unsigned long time33_simple_unsigned_long(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = hash * TIME_FACTOR + (unsigned long)arg->str[i];
    }
    return hash;
}

unsigned long time33_simple_shift(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = ((hash << 5) + hash) + (unsigned char)arg->str[i];
    }
    return hash;
}

unsigned long time33_simple_unsigned_char(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = hash * TIME_FACTOR + (unsigned char)arg->str[i];
    }
    return hash;
}

unsigned long time33_simple_truncate(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = hash * TIME_FACTOR + ((unsigned char)arg->str[i] & 0xff);
    }
    return hash;
}

unsigned long time33_apache(const str_arg_t* arg) {
    unsigned long hash = 5381;
    const char *p = arg->str;

    int length = arg->length;
    int* len = &length;

    if (*len <= 0) {
        for(p = arg->str; *p; p++) {
            hash = hash * TIME_FACTOR + *p;
        }
        *len = p - arg->str;
    }
    else {
        int i = *len;
        for (p = arg->str; i; i--, p++) {
            hash = hash * TIME_FACTOR + *p;
        }
    }
    return hash;
}

unsigned long time33_php(const str_arg_t* arg) {
    const char* arKey = arg->str;
    unsigned int nKeyLength = (unsigned int)arg->length;

	register unsigned long hash = 5381;

	/* variant with the hash unrolled eight times */
	for (; nKeyLength >= 8; nKeyLength -= 8) {
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
	}
	switch (nKeyLength) {
		case 7: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 6: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 5: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 4: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 3: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 2: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 1: hash = ((hash << 5) + hash) + *arKey++; break;
		case 0: break;
	}
	return hash;
}

unsigned long time33_debug(const str_arg_t* arg) {
    unsigned long hash = HASH_START_VALUE;
    for (int i = 0; i < arg->length; ++i) {
        hash = hash * TIME_FACTOR + ((unsigned long)arg->str[i] & 0xff);
    }
    return hash;
}
