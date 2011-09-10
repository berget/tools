#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

''' ping itunes hosts
'''

import os
import sys
import re
import datetime
import time
import logging
import logging.handlers

HOST_COUNT = 2000
PING_COUNT = 10
VALID_COUNT_THRESHOLD = 5
TOP_LIST_NUMBER = 10

def define_options():
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option('-c', '--count',
            type=int, dest='count', default=PING_COUNT,
            help='Stop after sending (and receiving) count ECHO_RESPONSE packets. default as %d' % PING_COUNT)
    parser.add_option('-n', '--number',
            type=int, dest='number', default = TOP_LIST_NUMBER,
            help='top N hosts list, default as %d' % TOP_LIST_NUMBER)
    parser.add_option('-o', '--log',
            dest='log', default=None,
            help='log file (append)')
    parser.add_option('-t', '--threshold',
            type=int, dest='threshold', default=VALID_COUNT_THRESHOLD,
            help='threshold of valid ping response, default as %d' % VALID_COUNT_THRESHOLD)
    parser.add_option('-q', '--quiet',
            action='store_false', dest='verbose', default=True,
            help='don\'t print status messages to stdout')
    options,args = parser.parse_args()
    return options


class _SingletonLogger(logging.getLoggerClass()):
    @classmethod
    def instance(cls):
        if not hasattr(cls, "_instance"):
            cls._instance = cls("")
        return cls._instance

logger = _SingletonLogger.instance()

def setup_rotating_log(logname):
    path = os.path.realpath(logname)
    dirname = os.path.dirname(path)
    if not os.path.isdir(dirname):
        os.makedirs(dirname)

    rotating_file_handler = logging.handlers.RotatingFileHandler(path, "a", 134217728, 7)
    fmt = logging.Formatter('%(asctime)s %(levelname)-5s %(filename)s:%(lineno)d %(message)s', '%x %X')
    rotating_file_handler.setFormatter(fmt)
    logger.addHandler(rotating_file_handler)

def setup_console_log():
    console = logging.StreamHandler()
    fmt = logging.Formatter('%(asctime)s %(levelname)-5s %(filename)s:%(lineno)d %(message)s', '%x %X')
    console.setFormatter(fmt)
    logger.addHandler(console)


class ApplePing(object):
    HOST_TPL = 'a%d.phobos.apple.com'

    RE_TIME = re.compile(r'ttl=\d+ time=([\d.]+?) ms')
    RE_IP = re.compile(r'\d+ bytes from (\d+\.\d+\.\d+\.\d+):')
    def __init__(self, options):
        self._host = ''

        self._ping_count = options.count
        logger.info('ping count: %d', self._ping_count)
        self._valid_count_threshold = options.threshold
        logger.info('valid count threshold: %d', self._valid_count_threshold)
        self._top_list_number = options.number
        logger.info('top list number: %d', self._top_list_number)

        self._top = []
        return

    def ping(self, host_number):
        self._host = self.HOST_TPL % host_number

        cmd = 'ping -c %d %s' % (self._ping_count, self._host)
        logger.info('$%s ...',  cmd)

        fp = os.popen(cmd)
        content = fp.read()
        fp.close()

        times = [float(i) for i in self.RE_TIME.findall(content)]

        if len(times) < self._valid_count_threshold:
            logger.error('failed to ping %s', self._host)
            return

        avg = sum(times) / len(times)

        ip = self._host
        match = self.RE_IP.search(content)
        if match:
            ip = match.group(1)

        info = {
                'host': self._host,
                'avg': avg,
                'ip': ip,
                }
        logger.info(info)

        self._top.append(info)
        self._top = sorted(self._top, key=lambda x:x['avg'])[:self._top_list_number]

        logger.info('show top %d hosts as follow' % self._top_list_number)
        index = 0
        for i in self._top:
            index += 1
            logger.info('%s %s', '%d.'%index, 'host: %(host)s, time: %(avg).2fms, ip: %(ip)s' % i)
        return

def main():
    ''' main function
    '''
    # define command line options
    options = define_options()
    # setup log for console if required
    if options.verbose:
        setup_console_log()
    # setup log for rotating file
    if options.log:
        setup_rotating_log(options.log)
    logger.info('start program')
    logger.info('setup console log handler')

    p = ApplePing(options)

    count_all = HOST_COUNT
    count_remain = HOST_COUNT
    start_time = time.time()

    for i in range(1, HOST_COUNT):
        count_remain -= 1
        logger.info('-' * 32)
        p.ping(i)

        delta = time.time() - start_time
        avg = delta / i 
        info = {
                'cost': datetime.timedelta(seconds=delta),
                'avg': avg,
                'count_remain': count_remain,
                'remain_time': datetime.timedelta(seconds=(count_remain * avg)),
                }
        logger.info(('progress: cost %(cost)s, '
                'avg: %(avg).2fs, '
                'remain: %(count_remain)d, '
                'remain time: %(remain_time)s'
                ) % info)
    logger.info('program done!')

if __name__ == '__main__':
    main()
