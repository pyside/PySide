# Test case for PySide bug 829
# Thomas Perl <thp.io/about>; 2011-04-16

import unittest
from PySide.QtCore import QSettings
from helper import adjust_filename

class QVariantConversions(unittest.TestCase):
    def testDictionary(self):
        s = QSettings(adjust_filename('bug_829.conf', __file__), QSettings.IniFormat)
        #Save value 
        s.setValue('x', {1: 'a'})
        s.sync()
        #Restore value
        self.assertEqual(s.value('x'), {1: 'a'})

if __name__ == '__main__':
    unittest.main()
