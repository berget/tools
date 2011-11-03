#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

'''
'''

import os
import sys
import socket, time
import datetime

def main():
    ''' main function
    '''
    port = 9527

    service = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    service.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    service.bind(("", port))
    service.listen(128)

    print 'listening on port: %d' % port
    while True:
        time.sleep(10)

        channel, info = service.accept()
        print 'connection from', info
        msg = str(datetime.datetime.now()) + '\n'
        channel.send(msg)
        channel.close()

    print 'Done'

if __name__ == '__main__':
    main()
