from PySide.QtCore import QObject, Slot, QTimer
from PySide.QtWebKit import QWebView

import unittest
from helper import UsesQApplication

functionID = -1

class JSFuncs(QObject):
    @Slot(str,result=str)
    def slot_str_str(self, x):
        global functionID
        functionID = 0
        return x.upper()

    @Slot(str,result='QVariant')
    def slot_str_list(self, x):
        global functionID
        functionID = 1
        return [x, x]

    @Slot('QStringList',result=str)
    def slot_strlist_str(self, x):
        global functionID
        functionID = 2
        return x[-1]

    @Slot('QVariant',result=str)
    def slot_variant_str(self, x):
        global functionID
        functionID = 3
        return str(x)

    @Slot('QVariantList',result=str)
    def slot_variantlist_str(self, x):
        global functionID
        functionID = 4
        return str(x[-1])

    @Slot('QVariantMap',result=str)
    def slot_variantmap_str(self, x):
        global functionID
        functionID = 5
        return str(x["foo"])



PAGE_DATA = "data:text/html,<!doctype html><html><body onload='%s'></body></html>"
FUNCTIONS_LIST = ['jsfuncs.slot_str_str("hello")',
                  'jsfuncs.slot_str_list("hello")',
                  'jsfuncs.slot_strlist_str(["hello","world"])',
                  'jsfuncs.slot_variant_str("hello")',
                  'jsfuncs.slot_variantlist_str(["hello","world"])',
                  'jsfuncs.slot_variantmap_str({"foo": "bar"})']


class TestJsCall(UsesQApplication):

    @classmethod
    def setUpClass(self):
        super(TestJsCall, self).setUpClass()

    def createInstance(self):
        global functionID
        self._view = QWebView()
        self._jsfuncs = JSFuncs()
        functionID = -1
        self._view.page().mainFrame().addToJavaScriptWindowObject("jsfuncs", self._jsfuncs)
        self._view.loadFinished[bool].connect(self.onLoadFinished)
        self._view.load(PAGE_DATA % FUNCTIONS_LIST[self._functionID])
        self._view.show()

    def testJsCall(self):
        self._functionID = 0
        self.createInstance()
        self.app.exec_()

    def onLoadFinished(self, result):
        global functionID
        self.assertEqual(self._functionID, functionID)
        if self._functionID == (len(FUNCTIONS_LIST) - 1):
            QTimer.singleShot(300, self.app.quit)
        else:
            #new test
            self._functionID += 1
            self.createInstance()


if __name__ == "__main__":
    unittest.main()
