#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Author: Zealot Ke <chzealot@gmail.com>
# Copyright (C) losthit.com 2011

'''24-Point Game
'''

import os
import sys
import math

class GameItem(object):
    MIN_DELTA = 0.0000001
    def __init__(self, item):
        if isinstance(item, GameItem):
            self.__value = item.value
            self.__expression = item.expression
        else:
            self.__value = item
            self.__expression = str(item)

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, value):
        self.__value = value

    @property
    def expression(self):
        return self.__expression

    @expression.setter
    def expression(self, expr):
        self.__expression = expr

    def __str__(self):
        return '(%s, "%s")' % (self.__value, self.__expression)

    def __eq__(self, _item):
        item = GameItem(_item)

        if self.__value == item.value:
            return True

        if math.fabs(float(self.__value) - float(item.value)) < self.MIN_DELTA:
            return True

        return False

class GameItemList(object):
    def __init__(self, *items):
        self._items = ()

        tmp_list = []
        for i in items:
            if isinstance(i, list) or isinstance(i, tuple):
                tmp_list += [GameItem(k) for k in i]
            else:
                tmp_list.append(GameItem(i))
        self._items = tuple(sorted(tmp_list, key=lambda x:x.value))
        return

    def __str__(self):
        return '(%s)' % (', '.join([str(i.value) for i in self._items]))

    def __iter__(self):
        for i in self._items:
            yield i

class GameResult(object):
    def __init__(self):
        self.valid = False
        self.expression = ''

    def __str__(self):
        return repr((self.valid, self.expression))


class Point24Game(object):
    MIN_DELTA = 0.00000001
    def __init__(self):
        self._factorial_dict, self._value_factorial_dict = self.__get_factorial_dict()

        self._get_expression_methods = (
                self._get_factorial,
                self._plus_one,
                self._plus_all,
                )

        return

    def __get_factorial_dict(self):
        value_factorial_dict = {1: 0}
        factorial_dict = {0: 1}

        for i in range(1, 17):
            factorial_dict[i] = factorial_dict[i-1] * i
            value_factorial_dict[factorial_dict[i]] = i

        return (factorial_dict, value_factorial_dict)

    def _eq(self, a, b):
        if a == b:
            return True

        a = float(a)
        b = float(b)

        delta = 0
        if a > b:
            delta = a - b
        else:
            delta = b - a

        if delta < self.MIN_DELTA:
            return True
        return False

    def get_one(self, items, value):
        result = GameResult()
        if len(items) == 1 and self._eq(items[0], value):
            return value
        return result

    def _plus_all(self, items, value):
        result = GameResult()

        if self._eq(sum([i.value for i in items]), value):
            result.valid = True
            result.expression = ' + '.join(map(lambda x:x.expression, items))

        return result

    def _get_factorial(self, items, value):
        result = GameResult()

        # reset: 4.00000000001 => 4
        int_value = int(value)
        if self._eq(value, int_value):
            value = int_value

        if value not in self._value_factorial_dict: return result

        result = self._get_expression(items, self._value_factorial_dict[value])
        if not result.valid:
            return result

        result.expression = '(%s)!' % result.expression

        return result

    def _plus_one(self, items, value):
        result = GameResult()
        return result

    def _get_expression(self, items, value=24):
        result = GameResult()

        for method in self._get_expression_methods:
            result = method(items, value)
            if result.valid:
                return result

        return result

    def get_expression(self, items, value=24):
        result = self._get_expression(items, value)
        if result.valid:
            return result.expression
        return ''

def main():
    ''' main function
    '''
    game = Point24Game()

    items = GameItemList(1, 1, 1, 1)

    expression = game.get_expression(items)
    print items, '-', repr(expression)

    print 'Done'

def test_game_item():
    a = GameItem(1)
    print 'a =', a
    a.value = '4'
    a.expression = '1 + 1 + 1 + 1'
    print 'a =', a
    b = GameItem(a)
    print 'b =', b
    print 'a == b:', a == b

    return

def test_game_item_list():
    a = GameItemList((1, 8, 5))
    b = GameItemList(3, 9, 6)
    for i in b:
        print i
    return

if __name__ == '__main__':
    main()
    #test_game_item()
    #test_game_item_list()
