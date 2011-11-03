#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

'''
'''

import os
import sys
import socket

def main():
    ''' main function
    '''
    host = 'localhost'
    port = 9527

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    msg = s.recv(4096)
    s.close()

    print 'server time is', msg.strip()

    print 'Done'

if __name__ == '__main__':
    main()
