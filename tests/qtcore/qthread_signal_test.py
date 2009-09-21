
'''Test cases for connecting signals between threads'''

import unittest

from PySide.QtCore import QThread, QObject, SIGNAL, QCoreApplication

thread_run = False

class Source(QObject):
    def __init__(self, *args):
        QObject.__init__(self, *args)

    def emit_sig(self):
        self.emit(SIGNAL('source()'))

class Target(QObject):
    def __init__(self, *args):
        QObject.__init__(self, *args)
        self.called = False

    def myslot(self):
        self.called = True

class ThreadJustConnects(QThread):
    def __init__(self, source, *args):
        QThread.__init__(self, *args)
        self.source = source
        self.target = Target()

    def run(self):
        global thread_run
        thread_run = True
        QObject.connect(self.source, SIGNAL('source()'), self.target.myslot)

        while not self.target.called:
            pass



class BasicConnection(unittest.TestCase):

    def testEmitOutsideThread(self):
        global thread_run

        app = QCoreApplication([])
        source = Source()
        thread = ThreadJustConnects(source)

        QObject.connect(thread, SIGNAL('finished()'), lambda: app.exit(0))
        thread.start()

        while not thread_run:
            pass

        source.emit_sig()

        app.exec_()
        thread.wait()

        self.assert_(thread.target.called)

if __name__ == '__main__':
    unittest.main()
