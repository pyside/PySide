
'''Test paint event override in python'''

import unittest

from PySide.QtCore import QTimerEvent
from PySide.QtGui import QApplication, QWidget

from helper import UsesQApplication

class MyWidget(QWidget):
    '''Sample widget'''

    def __init__(self, app=None):
        #Creates a new widget
        if app is None:
            app = QApplication([])

        super(MyWidget, self).__init__()
        self.app = app
        self.runs = 0
        self.max_runs = 5
        self.paint_event_called = False

    def timerEvent(self, event):
        #Timer event method
        self.runs += 1

        if self.runs == self.max_runs:
            self.app.quit()

        if not isinstance(event, QTimerEvent):
            raise TypeError('Invalid event type. Must be QTimerEvent')

    def paintEvent(self, event):
        #Empty paint event method
        # XXX: should be using super here, but somehow PyQt4
        # complains about paintEvent not present in super
        QWidget.paintEvent(self, event)
        self.paint_event_called = True


class PaintEventOverride(UsesQApplication):
    '''Test case for overriding QWidget.paintEvent'''

    qapplication = True

    def setUp(self):
        #Acquire resources
        super(PaintEventOverride, self).setUp()
        self.widget = MyWidget(self.app)

    def tearDown(self):
        #Release resources
        del self.widget
        super(PaintEventOverride, self).tearDown()

    def testPaintEvent(self):
        #Test QWidget.paintEvent override
        timer_id = self.widget.startTimer(100)
        self.widget.show()
        self.app.exec_()

        self.widget.killTimer(timer_id)

        self.assert_(self.widget.paint_event_called)
        self.assertEqual(self.widget.runs, 5)


if __name__ == '__main__':
    unittest.main()
