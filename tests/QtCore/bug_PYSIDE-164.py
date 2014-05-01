from PySide.QtCore import QCoreApplication, QEventLoop, QObject, Qt, QThread, QTimer, SIGNAL
import unittest


class Emitter(QThread):
    def __init__(self):
        QThread.__init__(self)

    def run(self):
        print "Before emit."
        self.emit(SIGNAL("signal(int)"), 0)
        print "After emit."

class Receiver(QObject):
    def __init__(self, eventloop):
        QObject.__init__(self)
        self.eventloop = eventloop

    def receive(self, number):
        print "Received number: %d" % number
        self.eventloop.exit(0)


class TestBugPYSIDE164(unittest.TestCase):

    def testBlockingSignal(self):
        app = QCoreApplication.instance() or QCoreApplication([])
        eventloop = QEventLoop()
        emitter = Emitter()
        receiver = Receiver(eventloop)
        emitter.connect(emitter, SIGNAL("signal(int)"),
                        receiver.receive, Qt.BlockingQueuedConnection)
        emitter.start()
        retval = eventloop.exec_()
        emitter.wait()
        self.assertEqual(retval, 0)

if __name__ == '__main__':
    unittest.main()
