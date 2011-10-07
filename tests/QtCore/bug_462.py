import unittest
import sys

from PySide.QtCore import QObject, QCoreApplication, QEvent, QThread

class MyEvent(QEvent):
    def __init__(self,i):
        print("TYPE:", type(QEvent.User))
        super(MyEvent,self).__init__(QEvent.Type(QEvent.User + 100 ))
        self.i = i

class MyThread (QThread):
    def __init__(self,owner):
        super(MyThread,self).__init__()
        self.owner=owner;

    def run(self):
        for i in range(3):
            e=MyEvent(i);
            QCoreApplication.postEvent(self.owner,e)

class MyBaseObject(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.events = []
        self.t = MyThread(self)
        self.t.start()

    def customEvent(self, event):
        self.events.append(event)
        if len(self.events) == 3:
            self.t.wait()
            self.app.quit()


class CheckForEventsTypes(unittest.TestCase):
    def testTypes(self):
        o = MyBaseObject()
        o.app = QCoreApplication(sys.argv)
        o.app.exec_()
        for e in o.events:
            self.assertTrue(isinstance(e, MyEvent))
        o.app = None

if __name__ == '__main__':
    unittest.main()
