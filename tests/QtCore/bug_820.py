import functools
import unittest

from PySide.QtCore import QObject, Slot, Signal, SIGNAL

def log_exception():
    def log_exception_decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwds):
            try:
                return func(*args, **kwds)
            except Exception:
                raise

        return wrapper

    return log_exception_decorator


def log_exception2():
    def log_exception_decorator(func):
        def wrapper(*args, **kwds):
            try:
                return func(*args, **kwds)
            except Exception:
                raise

        return wrapper

    return log_exception_decorator

class MyObject(QObject):

    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._mySlotcalled = False
        self._mySlot2called = False

    @Slot()
    @log_exception()
    def mySlot(self):
        self._mySlotcalled = True

    @Slot(name="mySlot2")
    @log_exception2()
    def mySlot2(self):
        self._mySlot2called = True

    def poke(self):
        self.events.emit()

    events = Signal()


class SlotWithDecoratorTest(unittest.TestCase):
    def testSlots(self):
        o = MyObject()
        self.assert_(o.metaObject().indexOfSlot("mySlot()") > 0)
        self.assert_(o.metaObject().indexOfSlot("mySlot2()") > 0)

        o.events.connect(o.mySlot)
        o.events.connect(o.mySlot2)
        o.poke()
        self.assertTrue(o._mySlotcalled)
        self.assertTrue(o._mySlot2called)

if __name__ == '__main__':
    unittest.main()

