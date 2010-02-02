
'''Test cases for QObject property and setProperty'''

import unittest

from PySide.QtCore import QObject, QVariant, QString

class PropertyCase(unittest.TestCase):
    '''Test case for QObject properties'''

    def testObjectNameProperty(self):
        #QObject.setProperty() for existing C++ property
        obj = QObject()
        self.assert_(obj.setProperty('objectName', QVariant('dummy')))
        self.assertEqual(obj.objectName(), 'dummy')

        self.assert_(obj.setProperty('objectName', QVariant('foobar')))
        self.assertEqual(obj.objectName(), 'foobar')

    def testDynamicProperty(self):
        #QObject.setProperty() for dynamic properties
        obj = QObject()

        # Should return false when creating a new dynamic property
        self.assert_(not obj.setProperty('dummy', QVariant('mydata')))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, QVariant))
        self.assert_(prop.isValid())
        self.assertEqual(obj.property('dummy').toString(), 'mydata')

        self.assert_(not obj.setProperty('dummy', QVariant('zigzag')))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, QVariant))
        self.assert_(prop.isValid())
        self.assertEqual(obj.property('dummy').toString(), 'zigzag')

        self.assert_(not obj.setProperty('dummy', QVariant(42)))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, QVariant))
        self.assert_(prop.isValid())
        # QVariant.toInt has a bool* arg in C++, so returns a tuple
        self.assertEqual(obj.property('dummy').toInt(), (42, True))

    def testQStringProperty(self):
        obj = QObject()
        self.assert_(not obj.setProperty('dummy', QString('data')))
        prop = obj.property('dummy')

        self.assert_(isinstance(prop, QVariant))
        self.assert_(prop.isValid())
        self.assertEqual(obj.property('dummy').toString(), QString('data'))

    def testImplicitQVariantProperty(self):
        obj = QObject()
        self.assert_(not obj.setProperty('dummy', 'data'))
        prop = obj.property('dummy')

        self.assert_(isinstance(prop, QVariant))
        self.assert_(prop.isValid())
        self.assertEqual(obj.property('dummy').toString(), 'data')

    def testInvalidProperty(self):
        #QObject.property() for invalid properties
        obj = QObject()

        prop = obj.property('dummy')
        self.assert_(not prop.isValid())


if __name__ == '__main__':
    unittest.main()
