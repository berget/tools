#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2012

'''
'''

import os
import sys

def time33(s):
    result = 5381
    for i in s:
        result = (result * 33 + ord(i)) & ((1<<65) - 1)
    return result

def utf8str(s):
    try:
        s = s.decode('gbk').encode('utf8')
    except:
        pass
    return s

def show_hash(s):
    #print '\"%s\", '%utf8str(s), (s, time33(s), hex(time33(s)))
    print '\"%s\", '%s, (s, time33(s), hex(time33(s)))

def main():
    ''' main function
    '''
    show_hash('清人')
    show_hash('病人')
    sys.exit()
    show_hash('')

    show_hash('\xe8\x95\xb2' * 1)

    show_hash('\xde\xad' * 1)
    show_hash('\xde\xad' * 2)
    show_hash('\xde\xad' * 3)
    show_hash('\xde\xad' * 4)
    show_hash('\xde\xad' * 5)
    print 'Done'

if __name__ == '__main__':
    main()
