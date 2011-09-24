#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

''' convert signature from personal into taobao version
'''

import os
import sys
from termcolor import colored

BASE_PATH = os.path.dirname(os.path.realpath(__file__))

class TBConvert(object):
    DEFAULT_VALID_SUFFIX = set(['.h', '.c', '.cpp', '.py'])
    DEFAULT_REPLACE_LIST = [
            ('Author:  Zealot Ke (Zealot), chzealot@gmail.com', 'Author:  Ke Jie (jinxi), jinxi.kj@taobao.com'),
            ('Company:  losthit.com', 'Company:  taobao.com'),
            ('# Author: Zealot Ke <chzealot@gmail.com>', '# Author: Ke Jie <jinxi.kj@taobao.com>'),
            ('# Copyright (C) losthit.com', '# Copyright (C) taobao.com'),
            ]
    def __init__(self):
        self._current = os.path.realpath(__file__)
        self._valid_suffix = self.DEFAULT_VALID_SUFFIX
        self._replace_list = self.DEFAULT_REPLACE_LIST
        self._commit = False

    def _(self, path):
        result = os.path.realpath(path)
        cwd = os.path.realpath(os.getcwd())

        if result == cwd:
            result = '.'
        elif result.startswith(cwd):
            result = '.%s' % result[len(cwd):]

        return result

    def red(self, s):
        result = colored(s, 'red')
        return result

    def green(self, s):
        result = colored(s, 'green')
        return result

    def cyan(self, s):
        result = colored(s, 'cyan')
        return result

    def magenta(self, s):
        result = colored(s, 'magenta')
        return result

    def start(self, path, commit):
        self._commit = commit

        path = os.path.realpath(path)
        if not os.path.exists(path):
            print 'Exit: path not exists: %s' % path
            return

        if os.path.isdir(path):
            self.convert_directory(path)
        else:
            self.convert_file(path)
        return

    def convert_directory(self, path):
        print 'convert directory: %s ...' % path
        for dirname, dirnames, filenames in os.walk(path):
            for i in filenames:
                path = os.path.realpath(os.path.join(dirname, i))
                self.convert_file(path)
        return

    def is_valid_file(self, path):
        for suffix in self._valid_suffix:
            if path.endswith(suffix):
                return True
        return False

    def load_file(self, path):
        fp = open(path)
        content = fp.read()
        fp.close()
        return content

    def save_file(self, path, content):
        fp = open(path, 'wb')
        fp.write(content)
        fp.close()

    def require_convert(self, content):
        for key, value in self._replace_list:
            if key in content:
                return True
        return False

    def convert(self, path, content):
        new_content = content
        for key, value in self._replace_list:
            if key not in content:
                continue
            print '- replace "%s" to "%s"' % (self.red(key), self.green(value))
            new_content = new_content.replace(key, value)

        if new_content != content and self._commit:
            print '- save "%s"' % self.magenta(self._(path))
            self.save_file(path, new_content)
        return

    def convert_file(self, path):
        if not self.is_valid_file(path):
            return
        if path == self._current:
            return

        content = self.load_file(path)

        if not self.require_convert(content):
            return

        print 'convert file: %s ...' % self.cyan(self._(path))
        self.convert(path, content)
        return

def main():
    ''' main function
    '''
    path = os.path.realpath(os.getcwd())
    if len(sys.argv) > 1:
        path = sys.argv[1]

    if path.startswith('-') or path in ('commit', ):
        path = os.path.realpath(os.getcwd())
    else:
        path = os.path.realpath(path)

    commit = False
    if 'commit' in sys.argv or '-c' in sys.argv:
        commit = True

    converter = TBConvert()

    converter.start(path, commit)

    print 'Done'

if __name__ == '__main__':
    main()
