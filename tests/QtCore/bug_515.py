""" Unittest for bug #515 """
""" http://bugs.openbossa.org/show_bug.cgi?id=515 """

from PySide import QtCore

callCleanup = False
def _cleanup():
    global callCleanup
    callCleanup = True

def _checkCleanup():
    global callCleanup
    assert(callCleanup)

app = QtCore.QCoreApplication([])
QtCore.qAddPostRoutine(_cleanup)
QtCore.qAddPostRoutine(_checkCleanup)
del app
