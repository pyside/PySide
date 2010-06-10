
''' Test case for QObject.signalsBlocked() and blockSignal()'''

import unittest
import os
from tempfile import mkstemp

from PySide.QtCore import QObject, SIGNAL, QFile, QThread, QTimer, Qt
from helper import UsesQCoreApplication

class MyThread(QThread):

    def run(self):
        self.emit(SIGNAL("test(const QString&)"), "INdT - PySide");

class TestThreadSignal(UsesQCoreApplication):

    __called__ = True
    def _callback(self, msg):
        self.assertEqual(msg, "INdT - PySide")
        self.__called__ = True
        self.app.quit()

    def testThread(self):
        t = MyThread()
        QObject.connect(t, SIGNAL("test(const QString&)"), self._callback);
        t.start()

        self.app.exec_()
        t.wait()
        self.assert_(self.__called__);

if __name__ == '__main__':
    unittest.main()
