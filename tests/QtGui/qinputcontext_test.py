
import unittest

from PySide.QtCore import Qt
from PySide.QtGui import QPushButton
from helper import UsesQApplication

class QInputContextTest(UsesQApplication):

    def testSetFocusWidget(self):
        widget = QPushButton()
        widget.show()

        if not widget.testAttribute(Qt.WA_InputMethodEnabled):
            widget.setAttribute(Qt.WA_InputMethodEnabled)

        context = self.app.inputContext()
        self.assertEqual(context.focusWidget(), None)

        context.setFocusWidget(widget)
        self.assertEqual(context.focusWidget(), widget)


if __name__ == '__main__':
    unittest.main()

