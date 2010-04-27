//! [0]
renderer = QSvgRenderer(QLatin1String("SvgCardDeck.svg"))
black = QGraphicsSvgItem()
red   = QGraphicsSvgItem()

black.setSharedRenderer(renderer)
black.setElementId(QLatin1String("black_joker"))

red.setSharedRenderer(renderer)
red.setElementId(QLatin1String("red_joker"))
//! [0]
