import unittest
from PySide.QtCore import QPointF
from PySide.QtGui import QTransform, QPolygonF, QPolygonF

class QTransformTest(unittest.TestCase):

    def testMap(self):
        transform = QTransform()
        values = (10.0, 20.0)
        tx, ty = transform.map(*values)
        self.assert_(isinstance(tx, float))
        self.assert_(isinstance(ty, float))
        self.assertEqual((tx, ty), values)

    def testquadToQuad(self):
        q1 = QPolygonF()
        q1.append(QPointF(10.0, 10.0))
        q1.append(QPointF(20.0, 10.0))
        q1.append(QPointF(10.0, -10.0))
        q1.append(QPointF(20.0, -10.0))

        q2 = QPolygonF()
        q2.append(QPointF(20.0, 20.0))
        q2.append(QPointF(30.0, 20.0))
        q2.append(QPointF(20.0, -20.0))
        q2.append(QPointF(30.0, -20.0))

        t1 = QTransform()
        r1 = QTransform.quadToQuad(q1, q2, t1)
        r2 = QTransform.quadToQuad(q1, q2)

        self.assertTrue(r1)
        self.assert_(r2)

        self.assertEqual(t1, r2)

    def testquadToSquare(self):
        q1 = QPolygonF()
        q1.append(QPointF(10.0, 10.0))
        q1.append(QPointF(20.0, 10.0))
        q1.append(QPointF(10.0, -10.0))
        q1.append(QPointF(20.0, -10.0))

        t1 = QTransform()
        r1 = QTransform.quadToSquare(q1, t1)
        r2 = QTransform.quadToSquare(q1)

        self.assertTrue(r1)
        self.assert_(r2)

        self.assertEqual(t1, r2)


    def testsquareToQuad(self):
        q1 = QPolygonF()
        q1.append(QPointF(10.0, 10.0))
        q1.append(QPointF(20.0, 10.0))
        q1.append(QPointF(10.0, -10.0))
        q1.append(QPointF(20.0, -10.0))

        t1 = QTransform()
        r1 = QTransform.squareToQuad(q1, t1)
        r2 = QTransform.squareToQuad(q1)

        self.assertTrue(r1)
        self.assert_(r2)

        self.assertEqual(t1, r2)


if __name__ == "__main__":
   unittest.main()

