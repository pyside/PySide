
'''Test cases for QLatin1String'''

import unittest

from PySide.QtCore import QString, QLatin1String, QObject


class ImplicitConvQLatin1String(unittest.TestCase):
    '''Tests for implicit conversion from QLatin1String to QString'''

    def testQLatin1String(self):
        '''QString implicit convertion from QLatin1String'''
        obj = QObject()
        obj.setObjectName(QLatin1String('dummy'))

        self.assertEqual(QString('dummy'), obj.objectName())

if __name__ == '__main__':
    unittest.main()

