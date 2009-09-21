#!/usr/bin/python
# -*- coding: utf-8 -*-

'''Unit tests to test QTranslator and translation in general.'''

import os
import unittest
from PySide.QtCore import QObject, QTranslator, QCoreApplication

from helper import UsesQCoreApplication

class TranslationTest(UsesQCoreApplication):
    '''Test case for Qt translation facilities.'''

    def setUp(self):
        super(TranslationTest, self).setUp()
        self.trdir = os.path.join(os.path.dirname(__file__), 'translations')
        # os.system is probably not the best way to do it
        os.system('lrelease %s/*.ts > /dev/null' % self.trdir)

    def tearDown(self):
        os.system('rm %s/*.qm > /dev/null' % self.trdir)
        super(TranslationTest, self).tearDown()

    def testLatin(self):
        #Set string value to Latin
        translator = QTranslator()
        translator.load(os.path.join(self.trdir, 'trans_latin.qm'))
        self.app.installTranslator(translator)

        obj = QObject()
        obj.setObjectName(obj.tr('Hello World!'))
        self.assertEqual(obj.objectName(), u'Orbis, te saluto!')

    def testRussian(self):
        #Set string value to Russian
        translator = QTranslator()
        translator.load(os.path.join(self.trdir, 'trans_russian.qm'))
        self.app.installTranslator(translator)

        obj = QObject()
        obj.setObjectName(obj.tr('Hello World!'))
        self.assertEqual(obj.objectName(), u'привет мир!')


if __name__ == '__main__':
    unittest.main()

