
'''Test cases for parent-child relationship'''

import unittest
from sys import getrefcount

from PySide.QtCore import *

class ParentRefCountCase(unittest.TestCase):
    '''Test case for the refcount changes of setParent'''

    def setUp(self):
        #Acquire resources
        self.parent = QObject()
        self.child = QObject()

    def tearDown(self):
        #Release resources
        del self.child
        del self.parent

    def testSetParent(self):
        #QObject.setParent() refcount changes
        self.assertEqual(getrefcount(self.child), 2)
        self.child.setParent(self.parent)
        self.assertEqual(getrefcount(self.child), 3)

    def testSetParentTwice(self):
        self.assertEqual(getrefcount(self.child), 2)
        self.child.setParent(self.parent)
        self.assertEqual(getrefcount(self.child), 3)
        self.child.setParent(self.parent)
        self.assertEqual(getrefcount(self.child), 3)

    def testConstructor(self):
        #QObject(QObject) refcount changes
        child = QObject(self.parent)
        self.assertEqual(getrefcount(child), 3)

class ParentCase(unittest.TestCase):
    '''Small collection of tests related to parent-child relationship'''

    def testSetParent(self):
        #QObject.setParent()
        parent = QObject()
        child = QObject()
        child.setParent(parent)

        self.assertEqual(parent, child.parent())

    def testParentConstructor(self):
        #QObject(parent)
        parent = QObject()
        child = QObject(parent)

        self.assertEqual(parent, child.parent())

        orig_repr = repr(child)
        del child
        self.assertEqual(orig_repr, repr(parent.children()[0]))

    def testChildren(self):
        #QObject.children()
        parent = QObject()
        children = [QObject(parent) for x in range(25)]

        self.assertEqual(parent.children(), children)

    def testFindChild(self):
        #QObject.findChild() with all QObject
        parent = QObject()
        name = 'object%d'
        children = [QObject(parent) for i in range(20)]

        for i, child in enumerate(children):
            child.setObjectName(name % i)

        for i, child in enumerate(children):
            self.assertEqual(child, parent.findChild(QObject, name % i))

    def testFindChildWithoutName(self):
        parent = QObject()
        name = 'object%d'
        children = [QObject(parent) for i in range(20)]

        for i, child in enumerate(children):
            child.setObjectName(name % i)

        child = parent.findChild(QObject)
        self.assertTrue(isinstance(child, QObject))

    def testFindChildren(self):
        #QObject.findChildren() with all QObject
        parent = QObject()
        target_name = 'foo'
        children = [QTimer(parent) for i in range(20)]
        children.extend([QObject(parent) for i in range(20)])

        for i, child in enumerate(children):
            if i % 5 == 0:
                child.setObjectName(target_name)
            else:
                child.setObjectName(str(i))

        # Emulates findChildren with the intended outcome
        target_children = [x for x in children if x.objectName() == target_name]
        test_children = parent.findChildren(QObject, target_name)
        self.assertEqual(target_children, test_children)

        # test findChildren default value
        res = parent.findChildren(QTimer)
        self.assertEqual(len(res), 20)

        # test findChildre with a regex
        res = parent.findChildren(QObject, QRegExp("^fo+"))
        self.assertEqual(res, test_children)


    def testParentEquality(self):
        #QObject.parent() == parent
        parent = QObject()
        child = QObject(parent)
        self.assertEqual(parent, child.parent())


class TestParentOwnership(unittest.TestCase):
    '''Test case for Parent/Child object ownership'''

    def testParentDestructor(self):
        parent = QObject()
        self.assertEqual(getrefcount(parent), 2)

        child = QObject(parent)
        self.assertEqual(getrefcount(child), 3)
        self.assertEqual(getrefcount(parent), 2)

        del parent
        self.assertEqual(getrefcount(child), 2)

        # this will fail because parent deleted child cpp object
        self.assertRaises(RuntimeError, lambda :child.objectName())

    # test parent with multiples children
    def testMultipleChildren(self):
        o = QObject()
        self.assertEqual(getrefcount(o), 2)

        c = QObject(o)
        self.assertEqual(getrefcount(c), 3)
        self.assertEqual(getrefcount(o), 2)

        c2 = QObject(o)
        self.assertEqual(getrefcount(o), 2)
        self.assertEqual(getrefcount(c), 3)
        self.assertEqual(getrefcount(c2), 3)

        del o
        self.assertEqual(getrefcount(c), 2)
        self.assertEqual(getrefcount(c2), 2)

        # this will fail because parent deleted child cpp object
        self.assertRaises(RuntimeError, lambda :c.objectName())
        self.assertRaises(RuntimeError, lambda :c2.objectName())

    # test recursive parent
    def testRecursiveParent(self):
        o = QObject()
        self.assertEqual(getrefcount(o), 2)

        c = QObject(o)
        self.assertEqual(getrefcount(c), 3)
        self.assertEqual(getrefcount(o), 2)

        c2 = QObject(c)
        self.assertEqual(getrefcount(o), 2)
        self.assertEqual(getrefcount(c), 3)
        self.assertEqual(getrefcount(c2), 3)

        del o
        self.assertEqual(getrefcount(c), 2)
        self.assertEqual(getrefcount(c2), 2)

        # this will fail because parent deleted child cpp object
        self.assertRaises(RuntimeError, lambda :c.objectName())
        self.assertRaises(RuntimeError, lambda :c2.objectName())

    # test parent transfer
    def testParentTransfer(self):
        o = QObject()
        self.assertEqual(getrefcount(o), 2)

        c = QObject()
        self.assertEqual(getrefcount(c), 2)

        c.setParent(o)
        self.assertEqual(getrefcount(c), 3)

        c.setParent(None)
        self.assertEqual(getrefcount(c), 2)

        del c
        del o


class ExtQObject(QObject):
    def __init__(self):
        QObject.__init__(self)

class ReparentingTest(unittest.TestCase):
    '''Test cases for reparenting'''

    def testParentedQObjectIdentity(self):
        object_list = []
        parent = QObject()
        for i in range(3):
            obj = QObject()
            object_list.append(obj)
            obj.setParent(parent)
        for child in parent.children():
            self.assertTrue(child in object_list)

    def testParentedExtQObjectType(self):
        object_list = []
        parent = QObject()
        for i in range(3):
            obj = ExtQObject()
            object_list.append(obj)
            obj.setParent(parent)
        for orig, child in zip(object_list, parent.children()):
            self.assertEqual(type(orig), type(child))

    def testReparentedQObjectIdentity(self):
        object_list = []
        old_parent = QObject()
        new_parent = QObject()
        for i in range(3):
            obj = QObject()
            object_list.append(obj)
            obj.setParent(old_parent)
        for obj in object_list:
            obj.setParent(new_parent)
        for child in new_parent.children():
            self.assertTrue(child in object_list)

    def testReparentedExtQObjectType(self):
        object_list = []
        old_parent = QObject()
        new_parent = QObject()
        for i in range(3):
            obj = ExtQObject()
            object_list.append(obj)
            obj.setParent(old_parent)
        for obj in object_list:
            obj.setParent(new_parent)
        for orig, child in zip(object_list, new_parent.children()):
            self.assertEqual(type(orig), type(child))


if __name__ == '__main__':
    unittest.main()
