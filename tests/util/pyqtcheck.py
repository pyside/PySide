#!/usr/bin/env python

import sys
from optparse import OptionParser

import PyQt4
from PyQt4 import QtCore, QtGui, QtNetwork

modules = [QtCore, QtGui, QtNetwork]

def search(klass, method=None):
    for module in modules:
        try:
            klass_obj = getattr(module, klass)
            print "%s *found* on module %s" % (klass, module.__name__)
        except AttributeError:
            print "%s not found on module %s" % (klass, module.__name__)
            continue

        if method is None:
            continue

        try:
            meth_obj = getattr(klass_obj, method)

            meth_name = ".".join([klass, method])
            klass_name = ".".join([module.__name__, klass])
            print "\"%s\" *found* on class %s" % (meth_name, klass_name)
        except AttributeError:
            print "\"%s\" not found on class %s" % (method, klass)


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    try:
        klass, method = argv[0].split(".")
    except:
        klass = argv[0]
        method = None

    search(klass, method)

if __name__ == '__main__':
    main()
