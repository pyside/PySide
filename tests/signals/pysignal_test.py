
import unittest
from PySide.QtCore import QObject, SIGNAL, SLOT
from PySide.QtGui import QSpinBox, QApplication, QWidget

class Dummy(QObject):
    """Dummy class used in this test."""
    def __init__(self, parent=None):
        QObject.__init__(self, parent)

class PythonSigSlot(unittest.TestCase):
    def setUp(self):
        self.called = False

    def tearDown(self):
        try:
            del self.args
        except:
            pass

    def callback(self, *args):
        if tuple(self.args) == args:
            self.called = True

    def testNoArgs(self):
        """Python signal and slots without arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo()'), self.callback)
        self.args = tuple()
        obj1.emit(SIGNAL('foo()'), *self.args)

        self.assert_(self.called)

    def testWithArgs(self):
        """Python signal and slots with integer arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo(int)'), self.callback)
        self.args = (42,)
        obj1.emit(SIGNAL('foo(int)'), *self.args)

        self.assert_(self.called)

app = QApplication([])

class SpinBoxPySignal(unittest.TestCase):
    """Tests the connection of python signals to QSpinBox qt slots."""

    qapplication = True

    def setUp(self):
        self.obj = Dummy()
        self.spin = QSpinBox()
        self.spin.setValue(0)

    def tearDown(self):
        del self.obj
        del self.spin

    def testValueChanged(self):
        """Emission of a python signal to QSpinBox setValue(int)"""
        QObject.connect(self.obj, SIGNAL('dummy(int)'), self.spin, SLOT('setValue(int)'))
        self.assertEqual(self.spin.value(), 0)

        self.obj.emit(SIGNAL('dummy(int)'), 4)
        self.assertEqual(self.spin.value(), 4)

    def testValueChangedMultiple(self):
        """Multiple emissions of a python signal to QSpinBox setValue(int)"""
        QObject.connect(self.obj, SIGNAL('dummy(int)'), self.spin, SLOT('setValue(int)'))
        self.assertEqual(self.spin.value(), 0)

        self.obj.emit(SIGNAL('dummy(int)'), 4)
        self.assertEqual(self.spin.value(), 4)

        self.obj.emit(SIGNAL('dummy(int)'), 77)
        self.assertEqual(self.spin.value(), 77)


class WidgetPySignal(unittest.TestCase):
    """Tests the connection of python signals to QWidget qt slots."""

    qapplication = True

    def setUp(self):
        self.obj = Dummy()
        self.widget = QWidget()

    def tearDown(self):
        del self.obj
        del self.widget

    def testShow(self):
        """Emission of a python signal to QWidget slot show()"""
        self.widget.hide()

        QObject.connect(self.obj, SIGNAL('dummy()'), self.widget, SLOT('show()'))
        self.assert_(not self.widget.isVisible())

        self.obj.emit(SIGNAL('dummy()'))
        self.assert_(self.widget.isVisible())

if __name__ == '__main__':
    unittest.main()
