#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2012

'''
'''

import os
import sys

def get_data(cmd, input):
    cmd_str = 'cat %s | %s' % (input, cmd)
    print cmd_str
    fp = os.popen(cmd_str)
    content = fp.read()
    fp.close()

    result = {}
    for line in content.split('\n'):
        items = line.split(' ')
        if len(items) != 2: continue
        result[items[0]] = int(items[1])
    return result

def get_ldata(input):
    cmd = './lconvert'
    return get_data(cmd, input)

def get_cdata(input):
    cmd = './cconvert'
    return get_data(cmd, input)

def get_hdata(input):
    cmd = './hconvert'
    return get_data(cmd, input)

def show_data(type, data):
    print 'show data for %s:' % type

    length = len(data)

    rdata = {}
    for key, value in data.iteritems():
        if value not in rdata:
            rdata[value] = set()
        rdata[value].add(key)

    rsize_data = {}
    for key, value in rdata.iteritems():
        if len(value) == 1:
            continue
        rsize_data[key] = len(value)
        if len(value) > 1:
            #c_count += len(value)
            print key, ' '.join(value)

    c_count = 0
    for key, value in rsize_data.iteritems():
        if value > 1:
            c_count += 1

    dist_data = {}
    for key, count in rsize_data.iteritems():
        if count not in dist_data:
            dist_data[count] = 0
        dist_data[count] += 1

    print u'- 词的数量: %d' % length
    print u'- 冲突数量: %d, %.4f%%' % (c_count, c_count*100.0/length)
    print u'- 冲突分布'
    for keyword_count, chongtu_count in sorted(dist_data.iteritems(), reverse=True, key=lambda x:x[0]):
        if keyword_count <= 1: continue
        print u'  # 词数量=%d 冲突数量=%d percent=%.4f%%' % (keyword_count, chongtu_count, chongtu_count * 100.0 / c_count)

def main():
    ''' main function
    '''
    input = 'data/word.list.utf8.txt'
    if len(sys.argv) > 1:
        input = sys.argv[1]

    #ldata = get_ldata(input)
    #show_data('ulong', ldata)

    #cdata = get_cdata(input)
    #show_data('uchar', cdata)

    cdata = get_hdata(input)
    show_data('uchar', cdata)

    print 'Done'

if __name__ == '__main__':
    main()
