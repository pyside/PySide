from PySide.QtCore import QObject, Slot, QTimer
from PySide.QtWebKit import QWebView, QWebPage

import unittest
from helper import UsesQApplication

class JSFuncs(QObject):
    functionID = -1
    @Slot(unicode,result=unicode)
    def slot_str_str(self, x):
        JSFuncs.functionID = 0
        return x.upper()

    @Slot(unicode,result='QVariant')
    def slot_str_list(self, x):
        JSFuncs.functionID = 1
        return [x, x]

    @Slot('QStringList',result=unicode)
    def slot_strlist_str(self, x):
        JSFuncs.functionID = 2
        return x[-1]

    @Slot('QVariant',result=unicode)
    def slot_variant_str(self, x):
        JSFuncs.functionID = 3
        return unicode(x)

    @Slot('QVariantList',result=unicode)
    def slot_variantlist_str(self, x):
        JSFuncs.functionID = 4
        return unicode(x[-1])

    @Slot('QVariantMap',result=unicode)
    def slot_variantmap_str(self, x):
        JSFuncs.functionID = 5
        return unicode(x["foo"])



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
        self._view = QWebView()
        self._jsfuncs = JSFuncs()
        JSFuncs.functionID = -1
        self._view.page().mainFrame().addToJavaScriptWindowObject("jsfuncs", self._jsfuncs)
        self._view.loadFinished[bool].connect(self.onLoadFinished)
        self._view.load(PAGE_DATA % FUNCTIONS_LIST[self._functionID])
        self._view.show()

    def testJsCall(self):
        self._functionID = 0
        self.createInstance()
        self.app.exec_()

    def onLoadFinished(self, result):
        self.assertEqual(self._functionID, JSFuncs.functionID)
        if self._functionID == len(FUNCTIONS_LIST) - 1:
            QTimer.singleShot(300, self.app.quit)
        else:
            #new test
            self._functionID += 1
            self.createInstance()


if __name__ == "__main__":
    unittest.main()
