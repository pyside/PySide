#!/usr/bin/python
'''Test suite for QtCore.QUrl'''

import unittest

from PySide.QtCore import QUrl

class QUrlBasicConstructor(unittest.TestCase):
    '''Tests the basic constructors'''

    def testBasic(self):
        #Default constructor for QUrl
        url = QUrl()
        self.assertEqual(url.toString(), "")

    def testSetAttributes(self):
        #Construct QUrl by set* methods
        url = QUrl()

        url.setScheme('ftp')
        self.assertEqual(url.toString(), 'ftp:')

        url.setHost('www.google.com')
        self.assertEqual(url.toString(), 'ftp://www.google.com')

        url.setPort(8080)
        self.assertEqual(url.toString(), 'ftp://www.google.com:8080')

        url.setPath('mail/view')
        self.assertEqual(url.toString(),
                        'ftp://www.google.com:8080/mail/view')

        url.setUserName('john')
        self.assertEqual(url.toString(),
                        'ftp://john@www.google.com:8080/mail/view')

        url.setPassword('abc123')
        self.assertEqual(url.toString(),
                        'ftp://john:abc123@www.google.com:8080/mail/view')

class QueryItemsTest(unittest.TestCase):
    '''Test query item management'''

    def testQueryItems(self):
        #QUrl.queryItems
        url = QUrl('http://www.google.com/search?q=python&hl=en')
        valid_data = [(('q'), ('python')), (('hl'), ('en'))]

        self.assertEqual(sorted(url.queryItems()), sorted(valid_data))

    def testEncodedQueryItems(self):
        #QUrl.encodedQueryItems
        url = QUrl('http://www.google.com/search?q=python&hl=en')
        valid_data = [(('q'), ('python')), (('hl'), ('en'))]

        self.assertEqual(sorted(url.encodedQueryItems()), sorted(valid_data))

    def testSetQueryItems(self):
        #QUrl.setQueryItems
        urla = QUrl('http://www.google.com/search?q=python&hl=en')
        urlb = QUrl('http://www.google.com/search')

        urlb.setQueryItems(urla.queryItems())

        self.assertEqual(urla, urlb)

    def testAddQueryItem(self):
        #QUrl.addQueryItem
        url = QUrl()
        valid_data = [('hl', 'en'), ('user', 'konqui')]

        url.addQueryItem(*valid_data[0])
        self.assertEqual(url.queryItems()[0], valid_data[0])

        url.addQueryItem(*valid_data[1])
        self.assertEqual(sorted(url.queryItems()), sorted(valid_data))

    def testAllEncodedQueryItemsValues(self):
        #QUrl.allEncodedQueryItemValues
        url = QUrl()
        key = 'key'
        valid_data = ['data', 'valid', 'test']

        for i, data in enumerate(valid_data):
            url.addQueryItem(key, data)
            self.assertEqual(url.allEncodedQueryItemValues(key),
                             list(valid_data[:i+1]))


if __name__ == '__main__':
    unittest.main()
