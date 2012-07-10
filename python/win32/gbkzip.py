#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2012

''' compress file and directory with gzip and GBK filename
'''

import os
import sys
import zipfile

class GbkZip(object):
    TMP_DIR = '.tmp'
    def __init__(self):
        self._zip = None
        self._zip_file = None
        self._finished = False

        self._ignore_names = set(['Thumbs.db', '.DS_Store'])
        return

    def __del__(self):
        if self._zip_file and not self._finished:
            if os.path.exists(self._zip_file):
                os.remove(self._zip_file)

    def _ignore(self, filename):
        if filename in self._ignore_names:
            return True
        return False

    def utf82gbk(self, s):
        return s.decode('utf8').encode('gb18030')

    def get_zip_filename(self, path):
        zip_file = path + '.zip'
        if not os.path.exists(zip_file):
            return zip_file

        dirname = os.path.dirname(path)
        basename = os.path.basename(path)
        index = 0
        while True:
            index += 1
            zip_file = os.path.join(dirname, '%s%d.zip' % (basename, index))
            if not os.path.exists(zip_file):
                break
        return zip_file

    def append_folders(self, topdir):
        prefix = os.path.dirname(topdir)
        for root, dirs, files in os.walk(topdir):
            for f in files:
                if self._ignore(f):
                    continue

                path = os.path.abspath(os.path.join(root, f))
                arcname = path[len(prefix)+1:]
                print 'z %s' % arcname
                self._zip.write(path, self.utf82gbk(arcname), zipfile.ZIP_DEFLATED)
        return

    def compress(self, path):
        path = os.path.abspath(path)

        self._zip_file = self.get_zip_filename(path)
        self._zip = zipfile.ZipFile(self._zip_file, 'w')

        if os.path.isfile(path):
            print 'z %s' % path
            self._zip.write(path, self.utf82gbk(basename), zipfile.ZIP_DEFLATED)
        else:
            self.append_folders(path)

        self._zip.close()
        self._finished = True
        return

def main():
    ''' main function
    '''
    filename = sys.argv[1]
    z = GbkZip()

    z.compress(filename)
    print 'Done'

if __name__ == '__main__':
    main()
