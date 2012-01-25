''' unit test for BUG #1104 '''

from PySide import QtCore
import py3kcompat as py3k
from helper import UsesQApplication
import unittest

class QSettingsTestCase(UsesQApplication):
    def testSetValueWithLongInts(self):
        s = QtCore.QSettings()
        s.setValue("test", [(py3k.unicode_('36/37'), 65824, 69888),
                            (py3k.unicode_('38/39'), 4294902272, 4294906368),
                            (py3k.unicode_('40/41'), 4294902528, 4294906624),
                            (py3k.unicode_('new'), 65824, 69888)])
        val = s.value("test")

if __name__ == "__main__":
    unittest.main()
