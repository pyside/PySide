#!/usr/bin/env python

"""Tests covering signal emission and receiving to python slots"""

import unittest

from PySide.QtCore import QObject, SIGNAL, SLOT

try:
    from PySide.QtGui import QSpinBox, QPushButton
    hasQtGui = True
except ImportError:
    hasQtGui = False

from helper import BasicPySlotCase, UsesQApplication

if hasQtGui:
    class ButtonPySlot(UsesQApplication, BasicPySlotCase):
        """Tests the connection of python slots to QPushButton signals"""

        def testButtonClicked(self):
            """Connection of a python slot to QPushButton.clicked()"""
            button = QPushButton('Mylabel')
            QObject.connect(button, SIGNAL('clicked()'), self.cb)
            self.args = tuple()
            button.emit(SIGNAL('clicked(bool)'), False)
            self.assert_(self.called)

        def testButtonClick(self):
            """Indirect qt signal emission using the QPushButton.click() method """
            button = QPushButton('label')
            QObject.connect(button, SIGNAL('clicked()'), self.cb)
            self.args = tuple()
            button.click()
            self.assert_(self.called)


if hasQtGui:
    class SpinBoxPySlot(UsesQApplication, BasicPySlotCase):
        """Tests the connection of python slots to QSpinBox signals"""

        def setUp(self):
            super(SpinBoxPySlot, self).setUp()
            self.spin = QSpinBox()

        def tearDown(self):
            del self.spin
            super(SpinBoxPySlot, self).tearDown()

        def testSpinBoxValueChanged(self):
            """Connection of a python slot to QSpinBox.valueChanged(int)"""
            QObject.connect(self.spin, SIGNAL('valueChanged(int)'), self.cb)
            self.args = [3]
            self.spin.emit(SIGNAL('valueChanged(int)'), *self.args)
            self.assert_(self.called)

        def testSpinBoxValueChangedImplicit(self):
            """Indirect qt signal emission using QSpinBox.setValue(int)"""
            QObject.connect(self.spin, SIGNAL('valueChanged(int)'), self.cb)
            self.args = [42]
            self.spin.setValue(self.args[0])
            self.assert_(self.called)

        def atestSpinBoxValueChangedFewArgs(self):
            """Emission of signals with fewer arguments than needed"""
            # XXX: PyQt4 crashes on the assertRaises
            QObject.connect(self.spin, SIGNAL('valueChanged(int)'), self.cb)
            self.args = (554,)
            self.assertRaises(TypeError, self.spin.emit, SIGNAL('valueChanged(int)'))

if hasQtGui:
    class QSpinBoxQtSlots(UsesQApplication):
        """Tests the connection to QSpinBox qt slots"""

        qapplication = True

        def testSetValueIndirect(self):
            """Indirect signal emission: QSpinBox using valueChanged(int)/setValue(int)"""
            spinSend = QSpinBox()
            spinRec = QSpinBox()

            spinRec.setValue(5)

            QObject.connect(spinSend, SIGNAL('valueChanged(int)'), spinRec, SLOT('setValue(int)'))
            self.assertEqual(spinRec.value(), 5)
            spinSend.setValue(3)
            self.assertEqual(spinRec.value(), 3)
            self.assertEqual(spinSend.value(), 3)

        def testSetValue(self):
            """Direct signal emission: QSpinBox using valueChanged(int)/setValue(int)"""
            spinSend = QSpinBox()
            spinRec = QSpinBox()

            spinRec.setValue(5)
            spinSend.setValue(42)

            QObject.connect(spinSend, SIGNAL('valueChanged(int)'), spinRec, SLOT('setValue(int)'))
            self.assertEqual(spinRec.value(), 5)
            self.assertEqual(spinSend.value(), 42)
            spinSend.emit(SIGNAL('valueChanged(int)'), 3)

            self.assertEqual(spinRec.value(), 3)
            #Direct emission shouldn't change the value of the emitter
            self.assertEqual(spinSend.value(), 42)

            spinSend.emit(SIGNAL('valueChanged(int)'), 66)
            self.assertEqual(spinRec.value(), 66)
            self.assertEqual(spinSend.value(), 42)


if __name__ == '__main__':
    unittest.main()
