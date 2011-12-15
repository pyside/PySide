# Test case for PySide bug 829
# Thomas Perl <thp.io/about>; 2011-04-16

import unittest
from PySide.QtCore import QSettings
import tempfile

class QVariantConversions(unittest.TestCase):
    def testDictionary(self):
        confFile = tempfile.NamedTemporaryFile(delete=False)
        s = QSettings(confFile.name, QSettings.IniFormat)
        # Save value
        s.setValue('x', {1: 'a'})
        s.sync()
        del s

        # Restore value
        s = QSettings(confFile.name, QSettings.IniFormat)
        self.assertEqual(s.value('x'), {1: 'a'})

if __name__ == '__main__':
    unittest.main()
