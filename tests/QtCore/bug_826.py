from PySide.QtCore import QEvent, Qt
import PySide

import unittest

TEST_EVENT_TYPE = QEvent.Type(QEvent.registerEventType())

class TestEvent(QEvent):
    TestEventType = QEvent.Type(QEvent.registerEventType())

    def __init__(self, rand=0):
        super(TestEvent, self).__init__(TestEvent.TestEventType)
        self._rand = rand

    def getRand(self):
        return self._rand


class TestEnums(unittest.TestCase):
    def testUserTypesValues(self):
        self.assert_(QEvent.User <= int(TestEvent.TestEventType) <= QEvent.MaxUser)
        self.assert_(QEvent.User <= int(TEST_EVENT_TYPE) <= QEvent.MaxUser)

    def testUserTypesRepr(self):
        self.assertEqual(eval(repr(TestEvent.TestEventType)), TestEvent.TestEventType)
        self.assertEqual(eval(repr(TEST_EVENT_TYPE)), TEST_EVENT_TYPE)

if __name__ == '__main__':
    unittest.main()
