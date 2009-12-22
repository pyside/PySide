import unittest
import random
from functools import partial

from PySide.QtCore import QObject, SIGNAL

try:
    from PySide.QtGui import QPushButton, QSpinBox
except ImportError:
    pass

from helper import BasicPySlotCase, UsesQApplication
from helper.decorators import requires


def random_gen(count=100, largest=99, lowest=0):
    for i in range(count):
        yield random.randint(lowest, largest)


class MultipleSignalConnections(unittest.TestCase):
    '''Base class for multiple signal connection testing'''

    def run_many(self, sender, signal, emitter, receivers, args=None):
        """Utility method to connect a list of receivers to a signal.
        sender - QObject that will emit the signal
        signal - string with the signal signature
        emitter - the callable that will trigger the signal
        receivers - list of BasicPySlotCase instances
        args - tuple with the arguments to be sent.
        """

        if args is None:
            args = tuple()

        for rec in receivers:
            rec.setUp()
            QObject.connect(sender, SIGNAL(signal), rec.cb)
            rec.args = tuple(args)

        emitter(*args)

        for rec in receivers:
            self.assert_(rec.called)


@requires('PySide.QtGui')
class QtGuiMultipleSlots(UsesQApplication, MultipleSignalConnections):
    '''Multiple connections to QtGui signals'''

    def testButtonClick(self):
        """Multiple connections to QPushButton.clicked()"""
        sender = QPushButton('button')
        receivers = [BasicPySlotCase() for x in range(30)]
        self.run_many(sender, 'clicked()', sender.click, receivers)

    def testSpinBoxValueChanged(self):
        """Multiple connections to QSpinBox.valueChanged(int)"""
        for test in random_gen(10):
            sender = QSpinBox()
            #FIXME if number of receivers if higher than 50, segfaults
            receivers = [BasicPySlotCase() for x in range(10)]
            self.run_many(sender, 'valueChanged(int)', sender.setValue,
                          receivers, (test,))


if __name__ == '__main__':
    unittest.main()
