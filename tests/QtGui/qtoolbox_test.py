
import unittest

from PySide.QtGui import QToolBox, QWidget, QIcon

from helper import UsesQApplication

class OwnershipControl(UsesQApplication):

    def setUp(self):
        super(OwnershipControl, self).setUp()
        self.toolbox = QToolBox()

    def tearDown(self):
        del self.toolbox
        super(OwnershipControl, self).tearDown()

    def testAddItem(self):
        # Was losing ownership of the widget.
        index = self.toolbox.addItem(QWidget(), 'item')
        item = self.toolbox.widget(index)
        self.assert_(isinstance(item, QWidget))

    def testAddItemWithIcon(self):
        index = self.toolbox.addItem(QWidget(), QIcon(), 'item')
        item = self.toolbox.widget(index)
        self.assert_(isinstance(item, QWidget))


if __name__ == '__main__':
    unittest.main()
