
'''Tests for inject codes and modifications on QFontMetrics
   and QFontMetricsF'''

import unittest
from PySide.QtGui import QFont, QFontMetrics, QFontMetricsF
from PySide.QtCore import QRect, QRectF, Qt, QSize, QSizeF
from helper import UsesQApplication


class QFontMetricsTest(UsesQApplication):
    '''Base class for QFontMetrics tests'''

    def setUp(self):
        super(QFontMetricsTest, self).setUp()
        self.font = QFont()
        self.metrics = QFontMetrics(self.font)

    def tearDown(self):
        del self.metrics
        del self.font
        super(QFontMetricsTest, self).tearDown()


class BoundingRectTest(QFontMetricsTest):
    '''Tests for QFontMetrics.boundingRect inject code'''

    def testIntDefault(self):
        '''QFontMetrics.boundingRect(int, int, int, int, ...) - default args'''
        rect = self.metrics.boundingRect(0, 0, 0, 0,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT')
        self.assertTrue(isinstance(rect, QRect))

    def testIntWithArg(self):
        '''QFontMetrics.boundingRect(int, int, int, int, ...) - single arg'''
        rect = self.metrics.boundingRect(0, 0, 0, 0,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 2)
        self.assertTrue(isinstance(rect, QRect))

    def testIntWithFull(self):
        '''QFontMetrics.boundingRect(int, int, int, int, ...) - all argss'''
        rect = self.metrics.boundingRect(0, 0, 0, 0,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, [1, 2, 3, 4, 5])
        self.assertTrue(isinstance(rect, QRect))

    def testIntTypeError(self):
        '''QFontMetrics.boundingRect(int, int, int, int, ...) - type error'''
        self.assertRaises(TypeError, self.metrics.boundingRect, 0, 0, 0, 0,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, ['aaaa', 'ase'])

    def testQRectDefault(self):
        '''QFontMetrics.boundingRect(QRect, ...) - default args'''
        arg = QRect(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT')
        self.assertTrue(isinstance(rect, QRect))

    def testQRectWithArg(self):
        '''QFontMetrics.boundingRect(QRect, ...) - only tabstops'''
        arg = QRect(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 2)
        self.assertTrue(isinstance(rect, QRect))

    def testQRectWithFull(self):
        '''QFontMetrics.boundingRect(QRect, ...) - all arguments'''
        arg = QRect(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20,
                                         [1, 2, 3, 4, 5])
        self.assertTrue(isinstance(rect, QRect))

    def testQRectTypeError(self):
        '''QFontMetrics.boundingRect(QRect, ...) - type error'''
        arg = QRect(0, 0, 100, 200)
        self.assertRaises(TypeError, self.metrics.boundingRect, arg,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, ['aaaa', 'ase'])


class SizeTest(QFontMetricsTest):
    '''Tests for QFontMetrics.size inject code'''

    def testDefault(self):
        '''QFontMetrics.size - default arguments'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT')
        self.assertTrue(isinstance(size, QSize))

    def testWithTabStops(self):
        '''QFontMetrics.size - only tabstops'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT', 2)
        self.assertTrue(isinstance(size, QSize))

    def testFull(self):
        '''QFontMetrics.size - all arguments'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT', 2, [1, 2, 3, 4])
        self.assertTrue(isinstance(size, QSize))

    def testTypeError(self):
        '''QFontMetrics.size - type error'''
        self.assertRaises(TypeError, self.metrics.size,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, ['aaaa', 'ase'])


class QFontMetricsFTest(UsesQApplication):
    '''Base class for QFontMetrics tests'''

    def setUp(self):
        super(QFontMetricsFTest, self).setUp()
        self.font = QFont()
        self.metrics = QFontMetricsF(self.font)

    def tearDown(self):
        del self.metrics
        del self.font
        super(QFontMetricsFTest, self).tearDown()


class FBoundingRectTest(QFontMetricsFTest):
    '''Tests for QFontMetricsF.boundingRect inject code'''

    def testQRectDefault(self):
        '''QFontMetricsF.boundingRect(QRectF, ...) - default args'''
        arg = QRectF(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT')
        self.assertTrue(isinstance(rect, QRectF))

    def testQRectWithArg(self):
        '''QFontMetricsF.boundingRect(QRectF, ...) - only tabstops'''
        arg = QRectF(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 2)
        self.assertTrue(isinstance(rect, QRectF))

    def testQRectWithFull(self):
        '''QFontMetricsF.boundingRect(QRectF, ...) - all arguments'''
        arg = QRectF(0, 0, 100, 200)
        rect = self.metrics.boundingRect(arg, Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20,
                                         [1, 2, 3, 4, 5])
        self.assertTrue(isinstance(rect, QRectF))

    def testQRectTypeError(self):
        '''QFontMetricsF.boundingRect(QRectF, ...) - type error'''
        arg = QRectF(0, 0, 100, 200)
        self.assertRaises(TypeError, self.metrics.boundingRect, arg,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, ['aaaa', 'ase'])


class FSizeTest(QFontMetricsFTest):
    '''Tests for QFontMetricsF.size inject code'''

    def testDefault(self):
        '''QFontMetricsF.size - default arguments'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT')
        self.assertTrue(isinstance(size, QSizeF))

    def testWithTabStops(self):
        '''QFontMetricsF.size - only tabstops'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT', 2)
        self.assertTrue(isinstance(size, QSizeF))

    def testFull(self):
        '''QFontMetricsF.size - all arguments'''
        size = self.metrics.size(Qt.TextExpandTabs | Qt.TextSingleLine,
                                 'PySide by INdT', 2, [1, 2, 3, 4])
        self.assertTrue(isinstance(size, QSizeF))

    def testTypeError(self):
        '''QFontMetricsF.size - type error'''
        self.assertRaises(TypeError, self.metrics.size,
                                         Qt.TextExpandTabs | Qt.AlignLeft,
                                         'PySide by INdT', 20, ['aaaa', 'ase'])


class QCharTest(QFontMetricsFTest):

    def testBoundingRect(self):
        retCh = self.metrics.boundingRectChar('a')
        self.assertEqual(type(retCh), QRectF)

    def testWith(self):
        retCh = self.metrics.widthChar('a')
        self.assertTrue(retCh > 0)

if __name__ == '__main__':
    unittest.main()
