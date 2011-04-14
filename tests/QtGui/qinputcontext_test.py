
import unittest

from PySide.QtGui import QPushButton
from helper import UsesQApplication

class QInputContextTest(UsesQApplication):

    def testSetFocusWidget(self):
        widget = QPushButton()
        widget.show()

        context = self.app.inputContext()
        self.assertEqual(context.focusWidget(), None)

        context.setFocusWidget(widget)
        self.assertEqual(context.focusWidget(), widget)


if __name__ == '__main__':
    unittest.main()

