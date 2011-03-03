//! [0]
def closeEvent(self, event):
    settings = QSettings("MyCompany", "MyApp")
    settings.setValue("geometry", self.saveGeometry())
    settings.setValue("windowState", self.saveState())
    QMainWindow.closeEvent(self, event)
//! [0]


//! [1]
def readSettings(self):
    settings = QSettings("MyCompany", "MyApp")
    restoreGeometry(settings.value("myWidget/geometry"))
    restoreState(settings.value("myWidget/windowState"))
//! [1]
