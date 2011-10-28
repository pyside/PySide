from PySide.QtCore import *
from PySide.QtSql import *
import unittest

class TestBug1013 (unittest.TestCase):

    def someSlot(self, row, record):
        record.setValue(0, 2)
        self._wasCalled = True

    def testIt(self):
        app = QCoreApplication([])
        db = QSqlDatabase.addDatabase('QSQLITE')
        db.setDatabaseName(':memory:')
        db.open()
        query = QSqlQuery()
        query.exec_('CREATE TABLE "foo" (id INT);')
        model = QSqlTableModel()
        model.setTable('foo')

        self._wasCalled = False
        model.primeInsert.connect(self.someSlot)
        model.select()
        QTimer.singleShot(0,lambda: model.insertRow(0) and app.quit())
        app.exec_()
        self.assertTrue(self._wasCalled)
        self.assertEqual(model.data(model.index(0, 0)), 2)

if __name__ == "__main__":
    unittest.main()
