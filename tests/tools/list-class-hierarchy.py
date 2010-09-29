#!/usr/bin/python

# This file is part of PySide: Python for Qt
#
# Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
#
# Contact: PySide team <contact@pyside.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
# 02110-1301 USA


# This is a small script printing out Qt binding class hierarchies
# for comparison purposes.
#
# Usage:
#
# ./list-class-hierarchy.py PySide > pyside.list
# ./list-class-hierarchy.py PyQt4 > pyqt4.list
#
# meld pyside.list pyqt4.list

import sys
import pdb
from inspect import isclass

ignore = ["staticMetaObject",
          "pyqtConfigure",
          "registerUserData",
          "thread",
         ]

def recurse_into(el,obj):
    #s = el.split('.')[-1]
    #pdb.set_trace()
    symbols = []
    for item in sorted(dir(obj)):
        if item[0]=='_':
            continue
        mel = el + '.' + item
        try:
            mobj = eval(mel)
        except Exception:
            continue

        if item in ignore:
            continue
        else:
            symbols.append(mel)

        if isclass(mobj):
            symbols += recurse_into(mel,mobj)

    return symbols

if __name__=='__main__':
    modules = [ 'QtCore',
                'QtGui',
                'QtHelp',
               #'QtMultimedia',
                'QtNetwork',
                'QtOpenGL',
                'QtScript',
                'QtScriptTools',
                'QtSql',
                'QtSvg',
                'QtTest',
               #'QtUiTools',
                'QtWebKit',
                'QtXml',
                'QtXmlPatterns' ]

    libraries = ["PySide", "PyQt4"]
    librarySymbols = {}
    for l in libraries:
        dictionary = []
        if l =="PyQt4":
            import sip
            sip.setapi('QDate',2)
            sip.setapi('QDateTime',2)
            sip.setapi('QString',2)
            sip.setapi('QTextStream',2)
            sip.setapi('QTime',2)
            sip.setapi('QUrl',2)
            sip.setapi('QVariant',2)

        for m in modules:
            exec "from %s import %s" % (l,m) in globals(), locals()
            dictionary += recurse_into(m, eval(m))
        librarySymbols[l] = dictionary

    print "PyQt4: ", len(librarySymbols["PyQt4"]), " PySide: ", len(librarySymbols["PySide"])

    for symbol in librarySymbols["PyQt4"]:
        if not (symbol in librarySymbols["PySide"]):
            print "Symbol not found in PySide:", symbol
