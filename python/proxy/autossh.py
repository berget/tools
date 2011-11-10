#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

''' build ssh-d proxy automaticly
'''

import os
import sys
import re
import time
import signal
import errno

from unilog import unilogger as logger
from unilog import setup_rotating_log, setup_console_log

BASE_PATH = os.path.dirname(os.path.realpath(__file__))
DEFAULT_PORT = 8080
DEFAULT_LOG_PATH = os.path.realpath(os.path.join(BASE_PATH, 'autosshd.log'))
DEFAULT_PID_FILE = os.path.realpath(os.path.join(BASE_PATH, 'autosshd.pid'))

def define_options():
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option('-o', '--log',
            dest='log', default=DEFAULT_LOG_PATH,
            help='path to log file, default as %s' % DEFAULT_LOG_PATH)
    parser.add_option('-p', '--port',
            type=int, dest='port', default=DEFAULT_PORT,
            help='ssh-d proxy port, default as %d' % DEFAULT_PORT)
    parser.add_option('-q', '--quiet',
            action='store_false', dest='verbose', default=True,
            help="don't print status messages to stdout")
    parser.add_option('-P', '--pid',
            dest='pid', default=DEFAULT_PID_FILE,
            help="pid file")
    options,args = parser.parse_args()
    return options

class AutoSSHProxy(object):
    def __init__(self, options):
        self._options = options

        pattern = r'(ssh -N -D %d )' % self._options.port
        pattern = r'^\d+\s*?(\d+).*?ssh -N -D %d ' % self._options.port
        logger.info('pattern = %s', pattern)
        self._pattern = re.compile(pattern)

    def get_proxy_pid(self):
        cmd = 'ps -ef'
        fp = os.popen(cmd)
        output = fp.read()
        fp.close()

        pid = None
        for line in output.split('\n'):
            line = line.strip()
            match = self._pattern.search(line)
            if not match: continue
            pid = int(match.group(1))

        return pid

    def timer_sleep(self, seconds):
        for i in xrange(seconds):
            logger.info('sleep %d seconds ...', seconds - i)
            time.sleep(1)
        return

    def start_proxy(self):
        logger.info('start proxy ...')
        cmd = 'nohup ssh -N -D %d zealot@losthit.com >&/dev/null &' % self._options.port
        cmd = 'ssh -N -D %d zealot@losthit.com' % self._options.port
        logger.info('run cmd: %s', cmd)

        pid = os.fork()
        if pid < 0:
            logger.error('failed to create process')
            return False
        elif pid > 0:
            logger.info('waiting for connecting remote host ...')
            self.timer_sleep(10)
            return False

        # run command in subprocess
        fp = os.popen(cmd)
        output = fp.read()
        fp.close()

        logger.info('proxy pid is: %s', self.get_proxy_pid())
        logger.info('output: %s', output)
        sys.exit()
        return False

    def stop_proxy(self, pid):
        logger.info('stop proxy ...')
        logger.info('kill pid: %s', pid)
        os.kill(pid, signal.SIGTERM)
        return

    def restart_proxy(self, pid):
        logger.info('restart proxy ...')
        self.stop_proxy(pid)
        logger.info('waiting for stopping proxy ...')
        self.timer_sleep(7)
        self.start_proxy()
        return

    def process_exists(self, pid):
        try:
            os.kill(pid, 0)
        except OSError, e:
            if e.errno == errno.ESRCH:
                return False
        return True

    def download_ok(self):
        import socks
        import socket
        socks.setdefaultproxy(socks.PROXY_TYPE_SOCKS5, "127.0.0.1", 8080)
        socket.socket = socks.socksocket
        socket.setdefaulttimeout(170)
        import urllib2

        return True
        is_ok = False
        for i in xrange(3):
            url = 'http://www.baidu.com/'
            logger.debug('download %s ...' % url)

            try:
                request = urllib2.Request(url)
                fp = urllib2.urlopen(request)
                response = fp.read()
                fp.close()
                if len(response) > 10:
                    is_ok = True
                    break
            except Exception, e:
                logger.error('download failed: %s', e)
        return is_ok

    def is_proxy_ok(self, pid):
        if not pid or not self.process_exists(pid):
            logger.info('process not exists: %s', pid)
            return False

        if not self.download_ok():
            logger.info('cannot dowload via proxy')
            return False
        logger.info('proxy is ok')
        return True

    def already_running(self, pidfile):
        try:
            pid = int(open(pidfile).read().strip())
            if pid and self.process_exists(pid):
                return True
        except:
            return False
        return False

    def save_pid(self):
        path = os.path.realpath(self._options.pid)
        dirname = os.path.dirname(path)
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        try:
            fp = open(path, 'wb').write(str(os.getpid()))
            fp.close()
        except Exception, e:
            logger.error('failed to save pid into: %s', path)
        return

    def start(self):
        logger.info('starting autossh proxy ...')
        if self.already_running(self._options.pid):
            logger.info('already running, exit')
            return
        self.save_pid()

        while True:
            proxy_pid = self.get_proxy_pid()
            if not proxy_pid:
                logger.info('proxy not exists, start it')
                self.start_proxy()

            if proxy_pid and not self.is_proxy_ok(proxy_pid):
                logger.info('proxy is failed, restart it, proxy_pid=%s', proxy_pid)
                self.restart_proxy(proxy_pid)
            time.sleep(10)
        return

def main():
    ''' main function
    '''
    # parse command line options
    options = define_options()

    if options.verbose:
        setup_console_log()
    setup_rotating_log(options.log)

    logger.info('start autossh ...')
    logger.info('log into %s', options.log)

    proxy = AutoSSHProxy(options)

    proxy.start()

    logger.info('done')

if __name__ == '__main__':
    main()
