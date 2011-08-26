#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide import QtCore, QtWebKit

from helper import UsesQApplication

class QWebPageHeadless(QtWebKit.QWebPage):
    # FIXME: This is not working, the slot is not overriden!
    # http://doc.qt.nokia.com/4.7-snapshot/qwebpage.html#shouldInterruptJavaScript
    @QtCore.Slot()
    def shouldInterruptJavaScript(self):
        self._interrupted = True
        QtCore.QTimer.singleShot(300, self._app.quit)
        return True

class TestSlotOverride(UsesQApplication):
    def testFunctionCall(self):
        page = QWebPageHeadless()
        page._interrupted = False
        page._app = self.app
        page.mainFrame().setHtml('<script>while(1);</script>')
        self.app.exec_()
        self.assertTrue(page._interrupted)

if __name__ == '__main__':
    unittest.main()
