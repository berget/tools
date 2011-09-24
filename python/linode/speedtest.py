#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

''' run speed test for linode data center
'''

import os
import sys
import re
import time
import urllib2

class Benchmark(object):
    SPEED_TEST_URL = 'http://www.linode.com/speedtest/'
    RE_FACILITIES = re.compile((r'<tr[^<>]*?>\s*?'
        r'<td>([^<>]+?)</td>\s*?'
        r'<td>([^<>]+?)</td>\s*?'
        r'<td><a href="([^<>]+?)">[^<>]*?</a></td>\s*?'
        r'</tr>'), re.DOTALL)
    RE_PING_TIME = re.compile('time=([\d.]+?) ms')
    def __init__(self):
        return

    def download(self, url):
        result = ''
        fp = urllib2.urlopen(url)
        result = fp.read()
        fp.close()
        return result

    def get_facilities(self):
        result = []
        content = self.download(self.SPEED_TEST_URL)
        for facility,hostname,url in self.RE_FACILITIES.findall(content):
            info = {
                    'facility': facility,
                    'hostname': hostname,
                    'url': url,
                    }
            result.append(info)
        return result

    def print_facilities(self, facilities):
        keys = ['facility', 'hostname', 'url']
        table = [keys,]
        table += [[i[k]for k in keys] for i in facilities]
        self._print_table(table)
        return

    def _print_table(self, table):
        if not table: return
        str_table = [[str(i) for i in line] for line in table]

        max_length = [0] * len(str_table[0])
        for i in xrange(len(max_length)):
            max_length[i] = max([len(line[i]) for line in str_table]) + 2

        for line in str_table:
            items = []
            for i in xrange(len(max_length)):
                length = max_length[i]
                items.append(line[i].ljust(length))
            print ''.join(items)
        return

    def ping_facilities(self, facilities):
        result = []
        for info in facilities:
            timems = self.ping_facility(info['hostname'])
            result.append((info['facility'], timems))
        print
        return result

    def ping_facility(self, hostname, count=7):
        if count < 3: count = 3
        result = 0
        cmd = 'ping -c %d %s' % (count, hostname)
        print '- %s ...' % cmd

        fp = os.popen(cmd)
        content = fp.read()
        fp.close()

        times = sorted(map(float, self.RE_PING_TIME.findall(content)))

        if len(times) < 1:
            return 0
        if len(times) >= 3:
            times = times[1:-1]
        result = sum(times) / len(times)
        return result

    def print_ping_times(self, ping_times):
        print 'show ping result as follow'
        table = [['facility', 'time(ms)'], ]
        table += sorted(ping_times, key=lambda x:x[1])
        self._print_table(table)
        return

    def test_download(self, facilities):
        result = []
        for info in facilities:
            print '- downlaod %s ...' % info['url']
            start_time = time.time()
            content = self.download(info['url'])
            delta = time.time() - start_time
            if delta == 0: delta = 0.0000001
            speed = len(content) / 1024.0 / delta # kB/s
            result.append((info['facility'], speed))
        return result

    def print_download_times(self, speedlist):
        print 'show download speed as follow'
        table = [['Facility', 'Speed(kB/s)'], ]
        table += sorted(speedlist, key=lambda x:x[1], reverse=True)
        self._print_table(table)
        return

    def run(self):
        facilities = self.get_facilities()
        self.print_facilities(facilities)
        print

        facility_pingtimes = self.ping_facilities(facilities)
        self.print_ping_times(facility_pingtimes)
        print

        download_times = self.test_download(facilities)
        self.print_download_times(download_times)
        print
        return

def main():
    ''' main function
    '''
    benchmark = Benchmark()

    benchmark.run()

    print 'Done'

if __name__ == '__main__':
    main()
