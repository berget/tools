#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

'''
'''

import os
import sys
from termcolor import colored

BASE_PATH = os.path.dirname(os.path.realpath(__file__))

class ConvertSpace(object):
    DEFAULT_VALID_SUFFIX = set(['.h', '.c', '.cpp', '.py', '.sh'])
    DEFAULT_REPLACE_LIST = [
            (' ', '.'),
            ]
    def __init__(self):
        self._current = os.path.realpath(__file__)
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
        for filename in os.listdir(path):
            if filename.startswith('.'): continue
            realpath = os.path.realpath(os.path.join(path, filename))
            self.convert_file(realpath)
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
        if path == self._current:
            return

        newpath = path
        for key, value in self._replace_list:
            newpath = newpath.replace(key, value)
        if newpath == path:
            return

        print 'convert %s' % self.cyan(self._(path))
        print '     => %s' % self.green(self._(path))
        if self._commit:
            os.rename(path, newpath)
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

    converter = ConvertSpace()

    converter.start(path, commit)

    print 'Done'

if __name__ == '__main__':
    main()

