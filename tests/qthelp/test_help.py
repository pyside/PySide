
import unittest

from PySide.QtHelp import QHelpEngine

from helper import UsesQApplication

class QHelpEngineCreation(UsesQApplication):

    def testConstructor(self):
        helpEngine = QHelpEngine('mycollection.qch')

if __name__ == '__main__':
    unittest.main()
