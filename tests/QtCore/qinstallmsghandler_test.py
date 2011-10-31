
'''Test cases for qInstallMsgHandler'''

import unittest
import sys

from PySide.QtCore import *

param = []

def handler(msgt, msg):
    global param
    param = [msgt, msg.strip()]

def handleruseless(msgt, msg):
    pass

class QInstallMsgHandlerTest(unittest.TestCase):

    def tearDown(self):
        # Ensure that next test will have a clear environment
        qInstallMsgHandler(None)

    def testNone(self):
        ret = qInstallMsgHandler(None)
        self.assertEqual(ret, None)

    def testRet(self):
        ret = qInstallMsgHandler(None)
        self.assertEqual(ret, None)
        refcount = sys.getrefcount(handleruseless)
        retNone = qInstallMsgHandler(handleruseless)
        self.assertEqual(sys.getrefcount(handleruseless), refcount + 1)
        rethandler = qInstallMsgHandler(None)
        self.assertEqual(rethandler, handleruseless)
        del rethandler
        self.assertEqual(sys.getrefcount(handleruseless), refcount)

    def testHandler(self):
        rethandler = qInstallMsgHandler(handler)
        qDebug("Test Debug")
        self.assertEqual(param[0], QtDebugMsg)
        self.assertEqual(param[1], "Test Debug")
        qWarning("Test Warning")
        self.assertEqual(param[0], QtWarningMsg)
        self.assertEqual(param[1], "Test Warning")
        qCritical("Test Critical")
        self.assertEqual(param[0], QtCriticalMsg)
        self.assertEqual(param[1], "Test Critical")

if __name__ == '__main__':
    unittest.main()

