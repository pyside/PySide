#!/usr/bin/python

import unittest
from PySide.QtCore import *
from PySide.QtXmlPatterns import QXmlSchema
from helper import UsesQCoreApplication

class QXmlPatternsTest(UsesQCoreApplication):

    def testSchema(self):
        data = QByteArray('''<?xml version=\"1.0\" encoding=\"UTF-8\"?>
                              <xsd:schema
                                 xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"
                                  xmlns=\"http://qt.nokia.com/xmlschematest\"
                                  targetNamespace=\"http://qt.nokia.com/xmlschematest\"
                                  version=\"1.0\"
                                  elementFormDefault=\"qualified\">
                              </xsd:schema>''')

        buf = QBuffer(data)
        buf.open(QIODevice.ReadOnly)

        schema = QXmlSchema()
        schema.load(buf)
        self.assert_(schema.isValid())


if __name__ == '__main__':
    unittest.main()

