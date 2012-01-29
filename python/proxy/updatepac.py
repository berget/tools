#!/usr/bin/env python2.5
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

'''
'''

import os
import sys
import urllib2

def define_options():
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option('-f', '--pac-file',
            dest='pac_file', default=None,
            help='path to save pac_file')
    options, args = parser.parse_args()
    return options

class Updater(object):
    AUTOPROXY_SSHD_PAC_URL = 'http://autoproxy2pac.appspot.com/pac/ssh-d'
    def __init__(self, options):
        self._options = options

        self._error_msg = ''

        self._keywords = ['function', 'decode64', 'asdf']
        return

    def download(self, url):
        result = None
        try:
            fp = urllib2.urlopen(url)
            try:
                content_list = []
                data = fp.read(4096)
                content_list.append(data)
                while data:
                    data = fp.read(4096)
                    if data: content_list.append(data)
                result = ''.join(content_list)
            except Exception, e:
                self._error_msg = 'download "%s" failed: %s' % (url, e)
            finally:
                fp.close()
        except Exception, e:
            self._error_msg = 'open "%s" failed: %s' % (url, e)
            return
        return result

    def validate(self, content):
        if not content:
            slef.alert('content is empty', self._error_msg)
            return False

        for keyword in self._keywords:
            if keyword not in content:
                msg = 'cannot found keyword: %s in "%s":'
                msg += '\n%s\n%s ...' % ('-'*32, content[:4096])
                self.alert('in valid content', msg)
        return True

    def alert(self, title, body):
        print '[alert] title: %s' % title
        print '[alert] body: %s' % body
        return

    def start(self):
        content = self.download(self.AUTOPROXY_SSHD_PAC_URL)

        if not self.validate(content):
            return
        return

def main():
    ''' main function
    '''
    options = define_options()

    updater = Updater(options)

    updater.start()

    print 'Done'

if __name__ == '__main__':
    main()
