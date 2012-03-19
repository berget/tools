#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2012

''' generate calender in confluence
support python >=2.5
'''

import os
import sys
import datetime
try:
    import calendar
except:
    print 'please use python: >=2.5'

def main():
    ''' main function
    '''
    today = datetime.datetime.today()

    c = calendar.Calendar()
    print '||  Monday  ||  Tuesday || Wednesday|| Thursday ||  Friday  || Saturday ||  Sunday ||'
    for day, weekday in c.itermonthdays2(today.year, today.month):
        day_string = str(day).rjust(2, '0')
        if day == 0:
            print '| %s ' % (' ' * 8),
        elif weekday in (5, 6):
            print '|  %s      ' % day_string,
        else:
            print '| [%s|#%s] ' % (day_string, day_string),
        if weekday == 6:
            print '|'
    return

if __name__ == '__main__':
    main()
