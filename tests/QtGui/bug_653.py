import unittest
from PySide.QtCore import *
from PySide.QtGui import *

class TestBug653(unittest.TestCase):
    """Crash after calling QWizardPage.wizard()"""
    def testIt(self):
        app = QApplication([])

        wizard = QWizard()
        page = QWizardPage()
        wizard.addPage(page)
        page.wizard() # crash here if the bug still exists due to a circular dependency
        wizard.show()

if __name__ == "__main__":
    unittest.main()