//! [0]
pixmap = QPixmap(":/splash.png")
splash = QSplashScreen(pixmap)
splash.show()

... # Loading some items
splash.showMessage("Loaded modules")

qApp.processEvents()

... # Establishing connections
splash.showMessage("Established connections")

qApp.processEvents()
//! [0]
