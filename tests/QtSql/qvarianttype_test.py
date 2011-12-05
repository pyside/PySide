'''Test cases for QVariant::Type converter'''
import unittest
import py3kcompat as py3k
from PySide.QtSql import QSqlField

class QVariantTypeTest(unittest.TestCase):
    def testQVariantType(self):
        f = QSqlField("name", str)
        self.assertEqual(f.type(), py3k.unicode)

        f = QSqlField("name", "QString")
        self.assertEqual(f.type(),  py3k.unicode)

        f = QSqlField("name", "double")
        self.assertEqual(f.type(), float)

        f = QSqlField("name", float)
        self.assertEqual(f.type(), float)

        f = QSqlField("name", int)
        self.assertEqual(f.type(), int)

        if not py3k.IS_PY3K:
            f = QSqlField("name", long)
            self.assertEqual(f.type(), int) # long isn't registered in QVariant:Type, just in QMetaType::Type

        #f = QSqlField("name", QObject)
        #self.assertEqual(f.type(), None)

        f = QSqlField("name", None)
        self.assertEqual(f.type(), None)

if __name__ == '__main__':
    unittest.main()
