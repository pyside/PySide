
'''Decorators for skipping test methods and test cases'''

import logging
import unittest


class requires(object):
    '''Skip if the given module is not found
    
    Usage:

    @requires('RequiredModule')
    class MyTestCase(unittest.TestCase):
        ...
    '''

    def __init__(self, *args):
        '''Setup this decorator. Args should be a list of
        module names'''
        self.skip = False

        for module in args:
            try:
                __import__(module)
            except ImportError:
                self.skip = True
                self.skipped = module
                break

    def __call__(self, klass):
        '''Replace a skipped class with a dummy testCase'''
        if not self.skip:
            return klass

        logging.warning('Module %s not found. Skipping %s' % (self.skipped,
                                                            klass.__name__))

        class SkipWrapper(unittest.TestCase):
            '''Dummy wrapper'''
            pass

        return SkipWrapper
