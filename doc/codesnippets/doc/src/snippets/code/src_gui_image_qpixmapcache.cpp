//! [0]
pm = QPixmap()
if not QPixmapCache.find("my_big_image", pm):
    pm.load("bigimage.png")
    QPixmapCache.insert("my_big_image", pm)
painter.drawPixmap(0, 0, pm)
//! [0]


//! [1]
pm = QPixmap()
if not QPixmapCache.find("my_big_image", pm):
    pm.load("bigimage.png")
    QPixmapCache.insert("my_big_image", pm)
painter.drawPixmap(0, 0, pm)
//! [1]
