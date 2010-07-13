#!/usr/bin/python
import unittest
from PySide.QtXml import QXmlSimpleReader

class QXmlSimpleReaderTest(unittest.TestCase):

    def testQXmlSimpleReaderInstatiation(self):
        '''QXmlSimpleReader must be a concrete class not an abstract one.'''
        reader = QXmlSimpleReader()

    def testQXmlSimpleReaderFeatures(self):
        '''Calls the QXmlSimpleReader.features method. The features checked
        (at least the first two) can be found in the QXmlSimpleReader documentation:
        http://qt.nokia.com/doc/4.6/qxmlsimplereader.html#setFeature
        '''
        reader = QXmlSimpleReader()
        hasFeature, ok = reader.feature('http://xml.org/sax/features/namespaces')
        self.assertEqual((hasFeature, ok), (True, True))

        hasFeature, ok = reader.feature('http://xml.org/sax/features/namespace-prefixes')
        self.assertEqual((hasFeature, ok), (False, True))

        hasFeature, ok = reader.feature('foobar')
        self.assertEqual((hasFeature, ok), (False, False))

    def testQXmlSimpleReaderProperty(self):
        '''Tries to get a non existent property.'''
        reader = QXmlSimpleReader()
        prop, ok = reader.property('foo')
        self.assertEqual((prop, ok), (None, False))
        reader.setProperty('foo', 'Something')

if __name__ == '__main__':
    unittest.main()

