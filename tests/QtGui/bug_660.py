import unittest
import py3kcompat as py3k
from PySide.QtGui import QStandardItemModel, QStandardItem

class MyItemModel(QStandardItemModel):
    def __init__(self,parent=None):
        super(MyItemModel,self).__init__(parent)
        self.appendRow([QStandardItem('Item 1'),])

    def mimeTypes(self):
        mtypes = super(MyItemModel,self).mimeTypes()
        mtypes.append(py3k.unicode_('application/my-form'))
        return mtypes

    def mimeData(self,indexes):
        self.__mimedata = super(MyItemModel,self).mimeData(indexes)
        self.__mimedata.setData(py3k.unicode_('application/my-form'), 'hi')
        return self.__mimedata

class TestBug660(unittest.TestCase):
    '''QMimeData type deleted prematurely when overriding mime-type in QStandardItemModel drag and drop'''
    def testIt(self):
        model = MyItemModel()
        model.mimeData([model.index(0, 0)]) # if it doesn't raise an exception it's all right!

if __name__ == '__main__':
    unittest.main()
