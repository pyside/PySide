import unittest
from helper import UsesQApplication
from PySide.QtGui import QPixmapCache, QPixmap


class QPixmapCacheTest(UsesQApplication):

    def testWithString(self):
        pm1 = QPixmap()
        ok = QPixmapCache.find('img', pm1)
        self.assertFalse(ok)

        pm2 = QPixmap()
        ok = QPixmapCache.insert('img', pm2)
        self.assertTrue(ok)

        pm3 = QPixmap()
        ok = QPixmapCache.find('img', pm3)
        self.assertTrue(ok)

    def testWithKey(self):
        pm1 = QPixmap()
        ok = QPixmapCache.find(QPixmapCache.Key(), pm1)
        self.assertFalse(ok)

        pm2 = QPixmap()
        key = QPixmapCache.insert(pm2)

        pm3 = QPixmap()
        ok = QPixmapCache.find(key, pm3)
        self.assertTrue(ok)


if __name__ == '__main__':
    unittest.main()

