#!/usr/bin/python
# -*- coding: utf-8 -*-

'''Unit tests to test QTranslator and translation in general.'''

import os
import unittest
import py3kcompat as py3k
from PySide.QtCore import QObject, QTranslator, QCoreApplication

from helper import UsesQCoreApplication

class TranslationTest(UsesQCoreApplication):
    '''Test case for Qt translation facilities.'''

    def setUp(self):
        super(TranslationTest, self).setUp()
        self.trdir = os.path.join(os.path.dirname(__file__), 'translations')

    def testLatin(self):
        #Set string value to Latin
        translator = QTranslator()
        translator.load(os.path.join(self.trdir, 'trans_latin.qm'))
        self.app.installTranslator(translator)

        obj = QObject()
        obj.setObjectName(obj.tr('Hello World!'))
        self.assertEqual(obj.objectName(), py3k.unicode_('Orbis, te saluto!'))

    def testRussian(self):
        #Set string value to Russian
        translator = QTranslator()
        translator.load(os.path.join(self.trdir, 'trans_russian.qm'))
        self.app.installTranslator(translator)

        obj = QObject()
        obj.setObjectName(obj.tr('Hello World!'))
        self.assertEqual(obj.objectName(), py3k.unicode_('привет мир!'))

    def testUtf8(self):
        translator = QTranslator()
        translator.load(os.path.join(self.trdir, 'trans_russian.qm'))
        self.app.installTranslator(translator)

        obj = QObject()
        obj.setObjectName(obj.trUtf8('Hello World!'))
        self.assertEqual(obj.objectName(), py3k.unicode_('привет мир!'))

    def testTranslateWithNoneDisambiguation(self):
        value = 'String here'
        obj = QCoreApplication.translate('context', value, None, QCoreApplication.UnicodeUTF8)
        self.assertTrue(isinstance(obj, py3k.unicode))
        self.assertEqual(obj, value)

if __name__ == '__main__':
    unittest.main()

