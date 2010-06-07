
'''Test cases for parent-child relationship'''

import unittest

from PySide.QtCore import QObject, QCoreApplication

class ChildrenCoreApplication(unittest.TestCase):
    '''Test case for calling QObject.children after creating a QCoreApp'''

    def testQCoreAppChildren(self):
        #QObject.children() after creating a QCoreApplication
        # Minimal test:
        # 1- Create QCoreApp
        # 2- Create parent and childrens
        # 3- While keeping the children alive, call parent.children()
        # 4- Delete parent
        app = QCoreApplication([])
        parent = QObject()
        children = [QObject(parent) for x in range(25)]
        # Uncomment the lines below to make the test pass
        # del children
        # del child2
        del parent # XXX Segfaults here
        self.assert_(True)


if __name__ == '__main__':
    unittest.main()
