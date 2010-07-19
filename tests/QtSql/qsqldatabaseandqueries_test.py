#!/usr/bin/python
'''Test cases for QtSql database creation, destruction and queries'''

import sys
import unittest

from PySide import QtSql
from PySide.QtCore import *
from PySide.QtGui import *

class Foo(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.model = QtSql.QSqlTableModel()

class SqlDatabaseCreationDestructionAndQueries(unittest.TestCase):
    '''Test cases for QtSql database creation, destruction and queries'''

    def setUp(self):
        #Acquire resources
        self.assertFalse(not QtSql.QSqlDatabase.drivers(), "installed Qt has no DB drivers")
        self.assertTrue("QSQLITE" in QtSql.QSqlDatabase.drivers(), "\"QSQLITE\" driver not available in this Qt version")
        self.db = QtSql.QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName(":memory:")
        self.assertTrue(self.db.open())

    def tearDown(self):
        #Release resources
        self.db.close()
        QtSql.QSqlDatabase.removeDatabase(":memory:")
        del self.db

    def testTableCreationAndDestruction(self):
        #Test table creation and destruction
        query = QtSql.QSqlQuery()
        query.exec_("CREATE TABLE dummy(id int primary key, dummyfield varchar(20))")
        query.exec_("DROP TABLE dummy")
        query.clear()

    def testTableInsertionAndRetrieval(self):
        #Test table creation, insertion and retrieval
        query = QtSql.QSqlQuery()
        query.exec_("CREATE TABLE person(id int primary key, "
                    "firstname varchar(20), lastname varchar(20))")
        query.exec_("INSERT INTO person VALUES(101, 'George', 'Harrison')")
        query.prepare("INSERT INTO person (id, firstname, lastname) "
                      "VALUES (:id, :firstname, :lastname)")
        query.bindValue(":id", 102)
        query.bindValue(":firstname", "John")
        query.bindValue(":lastname", "Lennon")
        query.exec_()

        lastname = ''
        query.exec_("SELECT lastname FROM person where id=101")
        self.assertTrue(query.isActive())
        query.next()
        lastname = query.value(0)
        self.assertEqual(lastname, 'Harrison')

    def testTableModelDeletion(self):
        app = QApplication([])

        bar = Foo()
        model = bar.model
        del bar
        del app

if __name__ == '__main__':
    unittest.main()

