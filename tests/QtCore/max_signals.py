import unittest

from PySide.QtCore import QObject, Signal, SIGNAL

class MyObject(QObject):
    pass


class TestSignalLimitless(unittest.TestCase):
    def test100DynamicSignals(self):
        self.count = 0
        def onSignal():
            self.count += 1

        #create 100 dynamic signals
        o = MyObject()
        for i in range(100):
            o.connect(SIGNAL('sig%d()'%i), onSignal)

        #chek if the signals are valid
        m = o.metaObject()
        for i in range(100):
            self.assert_(m.indexOfSignal('sig%d()'%i) > 0)

        #emit all 100 signals
        for i in range(100):
            o.emit(SIGNAL('sig%d()'%i))

        self.assertEqual(self.count, 100)

if __name__ == '__main__':
    unittest.main()
