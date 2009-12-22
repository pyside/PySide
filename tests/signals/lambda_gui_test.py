
'''Connecting lambda to gui signals'''

import unittest

from PySide.QtCore import QObject, SIGNAL

try:
    from PySide.QtGui import QSpinBox, QPushButton
except ImportError:
    pass

from helper import UsesQApplication
from helper import decorators


@decorators.requires('PySide.QtGui')
class QtGuiSigLambda(UsesQApplication):

    def testButton(self):
        #Connecting a lambda to a QPushButton.clicked()
        obj = QPushButton('label')
        QObject.connect(obj, SIGNAL('clicked()'),
                        lambda: setattr(obj, 'called', True))
        obj.click()
        self.assert_(obj.called)

    def testSpinButton(self):
        #Connecting a lambda to a QPushButton.clicked()
        obj = QSpinBox()
        arg = 444
        QObject.connect(obj, SIGNAL('valueChanged(int)'),
                        lambda x: setattr(obj, 'arg', 444))
        obj.setValue(444)
        self.assertEqual(obj.arg, arg)

if __name__ == '__main__':
    unittest.main()
