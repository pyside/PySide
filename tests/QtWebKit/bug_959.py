from PySide.QtCore import QObject, Slot, QTimer
from PySide.QtWebKit import QWebView
from PySide.QtGui import QApplication
from PySide import QtCore

import sys
import unittest

from helper import UsesQApplication

functionID = -1
currentWebView = None

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


def onLoadFinished( result ):
    QTimer.singleShot( 100, createNextWebView )

def createNextWebView():
    global functionID

    nListCount = len(FUNCTIONS_LIST) - 1
    functionID = functionID + 1
    print functionID

    if functionID < nListCount:
        createWebView( functionID )
    else:
        QTimer.singleShot(300, QApplication.instance().quit)


def createWebView( nIndex ):
    global functionID
    global currentWebView

    functionID = nIndex
    currentWebView = QWebView()
    currentWebView._jsfuncs = JSFuncs()
    currentWebView.page().mainFrame().addToJavaScriptWindowObject("jsfuncs", currentWebView._jsfuncs)
    QObject.connect( currentWebView, QtCore.SIGNAL('loadFinished( bool )'), onLoadFinished )
    currentWebView.load(PAGE_DATA % FUNCTIONS_LIST[ nIndex ])
    currentWebView.show()

class Bug959(UsesQApplication):

    def testJavaScriptInWebViewForCrash( self ):
        # wait for the webview load to be finished before creating the next webview
        # don't create the webview inside of onLoadFinished
        # also call onLoadFinished with the correct number of variables
        createNextWebView()
        self.app.exec_()

if __name__ == "__main__":
    unittest.main()
