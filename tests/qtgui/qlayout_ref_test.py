
'''Test cases for QLayout handling of child widgets references'''

import unittest
from sys import getrefcount

from PySide.QtGui import QHBoxLayout, QVBoxLayout, QGridLayout, QWidget
from PySide.QtGui import QStackedLayout, QFormLayout
from PySide.QtGui import QApplication, QPushButton, QLabel

from helper import UsesQApplication

class SaveReference(UsesQApplication):
    '''Test case to check if QLayout-derived classes increment the refcount
    of widgets passed to addWidget()'''

    # Adding here as nose can't see the qapplication attrib we inherit
    qapplication = True

    def setUp(self):
        #Acquire resources
        super(SaveReference, self).setUp()
        self.widget1 = QPushButton('click me')
        self.widget2 = QLabel('aaa')

    def tearDown(self):
        #Release resources
        del self.widget2
        del self.widget1
        super(SaveReference, self).tearDown()

    def checkLayoutReference(self, layout):
        #Checks the reference cound handling of layout.addWidget
        self.assertEqual(getrefcount(self.widget1), 2)
        layout.addWidget(self.widget1)
        self.assertEqual(getrefcount(self.widget1), 3)

        self.assertEqual(getrefcount(self.widget2), 2)
        layout.addWidget(self.widget2)
        self.assertEqual(getrefcount(self.widget2), 3)

        # Check if doesn't mess around with previous widget refcount
        self.assertEqual(getrefcount(self.widget1), 3)

    def testMoveLayout(self):
        l = QHBoxLayout()
        self.assertEqual(getrefcount(self.widget1), 2)
        l.addWidget(self.widget1)
        self.assertEqual(getrefcount(self.widget1), 2)

        w = QWidget()
        w.setLayout(l)
        self.assertEqual(getrefcount(self.widget1), 3)


    def testHBoxReference(self):
        #QHBoxLayout.addWidget reference count
        w = QWidget()
        self.checkLayoutReference(QHBoxLayout(w))

    def testVBoxReference(self):
        #QVBoxLayout.addWidget reference count
        w = QWidget()
        self.checkLayoutReference(QVBoxLayout(w))

    def testGridReference(self):
        #QGridLayout.addWidget reference count
        w = QWidget()
        self.checkLayoutReference(QGridLayout(w))

    def testFormReference(self):
        #QFormLayout.addWidget reference count
        w = QWidget()
        self.checkLayoutReference(QFormLayout(w))

    def testStackedReference(self):
        #QStackedLayout.addWidget reference count
        w = QWidget()
        self.checkLayoutReference(QStackedLayout(w))

class MultipleAdd(UsesQApplication):
    '''Test case to check if refcount is incremented only once when multiple
    calls to addWidget are made with the same widget'''

    qapplication = True

    def setUp(self):
        #Acquire resources
        super(MultipleAdd, self).setUp()
        self.widget = QPushButton('click me')
        self.win = QWidget()
        self.layout = QHBoxLayout(self.win)

    def tearDown(self):
        #Release resources
        del self.widget
        del self.layout
        del self.win
        super(MultipleAdd, self).tearDown()

    def testRefCount(self):
        #Multiple QLayout.addWidget calls on the same widget
        self.assertEqual(getrefcount(self.widget), 2)
        self.layout.addWidget(self.widget)
        self.assertEqual(getrefcount(self.widget), 3)
        self.layout.addWidget(self.widget)
        self.assertEqual(getrefcount(self.widget), 3)
        self.layout.addWidget(self.widget)
        self.assertEqual(getrefcount(self.widget), 3)

if __name__ == '__main__':
    unittest.main()
