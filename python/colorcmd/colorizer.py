#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

''' common methods for colorizer
'''

import os
import sys
import types

# dirname for current file
BASE_PATH = os.path.dirname(os.path.realpath(__file__))

class Colorizer(object):
    DEFAULT_PROGNAME = 'colorizer'  # program name, such as gcc, g++, svn, make, etc.
    DEFAULT_CONFIG_NAME = 'colorizer.rc'    # basename for config, such as colorgcc.rc, colorsvn.rc, colormake.rc, etc.
    def __init__(self):
        self._progname = os.path.basename(sys.argv[0])
        self._config_name = self.DEFAULT_CONFIG_NAME
        self._config_file = self._search_config_file(self._config_name)

        self.initialize()
        return

    def _search_config_file(self, config_name):
        result = None
        for dir in [BASE_PATH, os.path.expanduser('~'), '/etc']:
            path = os.path.abspath(os.path.join(dir, config_name))
            if os.path.isfile(path):
                result = path
                break
        return result

    def initialize(self):
        return

    def start(self):
        return

def main(items):
    ''' main function
    '''
    handler = None
    for name, obj in items.iteritems():
        if type(obj) != type(types.ObjectType): continue
        handler = obj
        if obj != Colorizer:
            break

    handler().start()
    print 'Done'

if __name__ == '__main__':
    main()
