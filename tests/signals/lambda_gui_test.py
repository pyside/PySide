
'''Connecting lambda to gui signals'''

import unittest

from PySide.QtCore import QObject, SIGNAL

try:
    from PySide.QtGui import QSpinBox, QPushButton
    hasQtGui = True
except ImportError:
    hasQtGui = False

from helper import UsesQApplication

if hasQtGui:
    class Control:
        def __init__(self):
            self.arg = False

    class QtGuiSigLambda(UsesQApplication):

        def testButton(self):
            #Connecting a lambda to a QPushButton.clicked()
            obj = QPushButton('label')
            ctr = Control()
            func = lambda: setattr(ctr, 'arg', True)
            QObject.connect(obj, SIGNAL('clicked()'), func)
            obj.click()
            self.assert_(ctr.arg)
            QObject.disconnect(obj, SIGNAL('clicked()'), func)


        def testSpinButton(self):
            #Connecting a lambda to a QPushButton.clicked()
            obj = QSpinBox()
            ctr = Control()
            arg = 444
            func = lambda x: setattr(ctr, 'arg', 444)
            QObject.connect(obj, SIGNAL('valueChanged(int)'), func)
            obj.setValue(444)
            self.assertEqual(ctr.arg, arg)
            QObject.disconnect(obj, SIGNAL('valueChanged(int)'), func)

if __name__ == '__main__':
    unittest.main()
