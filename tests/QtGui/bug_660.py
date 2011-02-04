import unittest
from PySide.QtCore import *
from PySide.QtGui import *

class MyItemModel(QStandardItemModel):
    def __init__(self,parent=None):
        super(MyItemModel,self).__init__(parent)
        self.appendRow([QStandardItem('Item 1'),])

    def mimeTypes(self):
        mtypes = super(MyItemModel,self).mimeTypes()
        mtypes.append(u'application/my-form')
        return mtypes

    def mimeData(self,indexes):
        self.__mimedata = super(MyItemModel,self).mimeData(indexes)
        self.__mimedata.setData(u'application/my-form', 'hi')
        return self.__mimedata

class TestBug660(unittest.TestCase):
    '''QMimeData type deleted prematurely when overriding mime-type in QStandardItemModel drag and drop'''
    def testIt(self):
        model = MyItemModel()
        model.mimeData([model.index(0, 0)]) # if it doesn't raise an exception it's all right!

if __name__ == '__main__':
    unittest.main()
