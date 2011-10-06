import unittest
from helper import UsesQApplication
from PySide.QtGui import QPixmapCache, QPixmap


class QPixmapCacheTest(UsesQApplication):

    def testWithString(self):
        pm1 = QPixmap()
        ok = QPixmapCache.find('img', pm1)
        self.assertFalse(ok)

        self.assertEqual(QPixmapCache.find('img'), None)

        pm2 = QPixmap()
        ok = QPixmapCache.insert('img', pm2)
        self.assertTrue(ok)

        pm3 = QPixmap()
        ok = QPixmapCache.find('img', pm3)
        self.assertTrue(ok)
        b1 = QPixmapCache.find('img').toImage().bits()
        b2 = pm3.toImage().bits()
        self.assertEqual(QPixmapCache.find('img').toImage().bits(), pm3.toImage().bits())

    def testWithKey(self):
        pm1 = QPixmap()
        ok = QPixmapCache.find(QPixmapCache.Key(), pm1)
        self.assertFalse(ok)

        self.assertEqual(QPixmapCache.find(QPixmapCache.Key()), None)

        pm2 = QPixmap()
        key = QPixmapCache.insert(pm2)

        pm3 = QPixmap()
        ok = QPixmapCache.find(key, pm3)
        self.assertTrue(ok)

        self.assertEqual(QPixmapCache.find(key).toImage().bits(), pm3.toImage().bits())

if __name__ == '__main__':
    unittest.main()

