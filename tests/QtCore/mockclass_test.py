# Test case for PySide bug 634
# http://bugs.pyside.org/show_bug.cgi?id=634
# Marcus Lindblom <macke@yar.nu>; 2011-02-16

import unittest
from PySide.QtCore import QCoreApplication

class Mock(object):
    def __init__(self):
        self.called = False
        self.return_value = None

    def __call__(self, *args, **kwargs):
        self.called = True
        return self.return_value


class MockClassTest(unittest.TestCase):
    def testMockQCoreApplication(self):
        mock = Mock()
        setattr(QCoreApplication, 'instance', mock)
        QCoreApplication.instance()
        self.assert_(mock.called)

if __name__ == '__main__':
    unittest.main()

