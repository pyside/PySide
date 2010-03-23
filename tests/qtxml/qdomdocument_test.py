#!/usr/bin/python
import unittest
from PySide.QtCore import QByteArray
from PySide.QtXml import QDomDocument, QDomElement

class QDomDocumentTest(unittest.TestCase):

    def setUp(self):
        self.dom = QDomDocument()

        self.goodXmlData = QByteArray('''
        <typesystem package="PySide.QtXml">
            <value-type name="QDomDocument"/>
            <value-type name="QDomElement"/>
        </typesystem>
        ''')

        self.badXmlData = QByteArray('''
        <typesystem package="PySide.QtXml">
            <value-type name="QDomDocument">
        </typesystem>
        ''')

    def tearDown(self):
        del self.dom
        del self.goodXmlData
        del self.badXmlData

    def testQDomDocumentSetContentWithBadXmlData(self):
        '''Sets invalid xml as the QDomDocument contents.'''
        ok, errorStr, errorLine, errorColumn = self.dom.setContent(self.badXmlData, True)
        self.assertFalse(ok)
        self.assertEqual(errorStr, 'tag mismatch')
        self.assertEqual(errorLine, 4)
        self.assertEqual(errorColumn, 21)

    def testQDomDocumentSetContentWithGoodXmlData(self):
        '''Sets valid xml as the QDomDocument contents.'''
        ok, errorStr, errorLine, errorColumn = self.dom.setContent(self.goodXmlData, True)
        self.assert_(ok)
        self.assertEqual(errorStr, '')
        self.assertEqual(errorLine, 0)
        self.assertEqual(errorColumn, 0)

    def testQDomDocumentData(self):
        '''Checks the QDomDocument elements for the valid xml contents.'''

        def checkAttribute(element, attribute, value):
            self.assert_(isinstance(root, QDomElement))
            self.assertFalse(element.isNull())
            self.assert_(element.hasAttribute(attribute))
            self.assertEqual(element.attribute(attribute), value)

        ok, errorStr, errorLine, errorColumn = self.dom.setContent(self.goodXmlData, True)
        root = self.dom.documentElement()
        self.assertEqual(root.tagName(), 'typesystem')
        checkAttribute(root, 'package', 'PySide.QtXml')

        child = root.firstChildElement('value-type')
        checkAttribute(child, 'name', 'QDomDocument')

        child = child.nextSiblingElement('value-type')
        checkAttribute(child, 'name', 'QDomElement')

if __name__ == '__main__':
    unittest.main()

