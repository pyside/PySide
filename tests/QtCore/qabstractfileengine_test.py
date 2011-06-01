#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
import os
from PySide.QtCore import QAbstractFileEngineIterator, QAbstractFileEngine, QAbstractFileEngineHandler, QDir


class TestFSIterator(QAbstractFileEngineIterator):
    def __init__(self, parent, filters, filterNames):
        QAbstractFileEngineIterator.__init__(self, filters, filterNames)
        self.index = -1
        self._list = ['.', '..']
        if parent == '/bup':
            self._list += ['A', 'B', 'C']

    def next(self):
        self.index += 1
        return self.currentFileName()

    def hasNext(self):
        return (self.index + 1) < len(self._list)

    def currentFileName(self):
        if self.index < len(self._list):
            return self._list[self.index]
        return None


class TestFS(QAbstractFileEngine):
    def __init__(self, path):
        QAbstractFileEngine.__init__(self)
        self.path = path

    def beginEntryList(self, filters, filterNames):
        return TestFSIterator(self.path, filters, filterNames)

    def fileFlags(self, _ = QAbstractFileEngine.FileInfoAll):
        return QAbstractFileEngine.ExistsFlag\
               |QAbstractFileEngine.ReadOwnerPerm\
               |QAbstractFileEngine.ReadUserPerm\
               |QAbstractFileEngine.ReadGroupPerm\
               |QAbstractFileEngine.ReadOtherPerm\
               |QAbstractFileEngine.DirectoryType

    def fileName(self, path=QAbstractFileEngine.DefaultName):
        if path == QAbstractFileEngine.DefaultName:
            return self.path
        return os.path.basename(self.path)

    def setFileName(self, path):
        self.path = path

class TestFSHandler(QAbstractFileEngineHandler):
    def __init__(self):
        QAbstractFileEngineHandler.__init__(self)

    def create(self, path):
        if path.startswith('/bup'):
            return TestFS(path)
        return None

class QAbstractFileEngineTest(unittest.TestCase):

    def testBeginEntryList(self):
        obj = TestFSHandler()
        qdir = QDir('/bup')
        for n1, n2 in zip(qdir.entryList(), ['.', '..', 'A', 'B', 'C']):
            self.assertEqual(n1, n2)
        self.assertEqual(len(qdir.entryList()), 5)


if __name__ == '__main__':
    unittest.main()

