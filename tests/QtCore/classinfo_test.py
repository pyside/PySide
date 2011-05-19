import unittest
import sys
from PySide.QtCore import QObject, ClassInfo

@ClassInfo(author='pyside',url='http://www.pyside.org')
class MyObject(QObject):
    pass

class TestClassInfo(unittest.TestCase):
    def testMetaData(self):
        o = MyObject()
        mo = o.metaObject()
        self.assertEqual(mo.classInfoCount(), 2)

        ci = mo.classInfo(0) #author
        self.assertEqual(ci.name(), 'author')
        self.assertEqual(ci.value(), 'pyside')

        ci = mo.classInfo(1) #url
        self.assertEqual(ci.name(), 'url')
        self.assertEqual(ci.value(), 'http://www.pyside.org')

if __name__ == '__main__':
    if sys.version_info[0] < 2:
        sys.exit(0)
    elif (sys.version_info[0] == 2) and (sys.version_info[1] <= 5):
        sys.exit(0)
    else:
        unittest.main()
