#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Ke Jie(Zealot Ke, kejie@kuxun.com)

''' auto-build ssh-d proxy
'''

import os
import sys
import time
import errno

BASE_PATH = os.path.dirname(os.path.abspath(__file__))

class Proxy(object):
    DEFAULT_PORT = 8090
    DEFAULT_PID_PATH = os.path.join(BASE_PATH, 'autosshd.pid')
    def __init__(self):
        self._port = self.DEFAULT_PORT
        self._pid_path = self.DEFAULT_PID_PATH
        self._command = 'ssh -N -D %d zealot@losthit.com' % self._port

    def start_forever(self):
        if self.has_instance():
            print 'exit: instance exists.'
            return

        while True:
            self.start()
        return

    def start(self):
        fp = open(self._pid_path, 'w')
        fp.write(str(os.getpid()))
        fp.close()

        print '$ %s' % self._command
        os.system(self._command)

    def has_instance(self):
        return self._has_instance(self._pid_path)

    def _has_instance(self, pid_path):
        if not os.path.exists(pid_path):
            return False

        fp = open(pid_path)
        pid = int(fp.read().strip())
        fp.close()

        return self._exists_process(pid)

    def _exists_process(self, pid):
        if pid < 0:
            return False
        try:
            os.kill(pid, 0)
        except OSError, e:
            return e.errno == errno.EPERM
        else:
            return True

def main():
    ''' main function
    '''
    p = Proxy()
    p.start_forever()
    print 'Done'

if __name__ == '__main__':
    main()
