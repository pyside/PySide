//! [0]

def paintLayout(self, painter, item):
    layout = item.layout()

    if layout:
        for layout_item in layout:
            self.paintLayout(painter, layout_item)

    painter.drawRect(item.geometry())

def paintEvent(self, event):
    painter = QPainter(self)
    if self.layout():
        self.paintLayout(painter, self.layout())

//! [0]


//! [1]
child = layout.takeAt(0)
while child:
    ...
    del child
//! [1]
