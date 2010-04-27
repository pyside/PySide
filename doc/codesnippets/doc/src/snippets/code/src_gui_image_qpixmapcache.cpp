//! [0]
pm = QPixmapCache.find("my_big_image")
if not pm.isNull():
    pm.load("bigimage.png")
    QPixmapCache.insert("my_big_image", pm)
painter.drawPixmap(0, 0, pm)
//! [0]


//! [1]
pm = QPixmapCache.find("my_big_image")
if not pm.isNull():
    pm.load("bigimage.png")
    QPixmapCache.insert("my_big_image", pm)
painter.drawPixmap(0, 0, pm)
//! [1]
