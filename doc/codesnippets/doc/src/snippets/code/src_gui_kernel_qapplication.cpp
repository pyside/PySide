//! [0]
def main():
    if Qt.Q_WS_X11
        useGUI = getenv("DISPLAY") != 0
    else:
        useGUI = True

    app = QApplication(sys.argv, useGUI)

    if useGUI:
       # start GUI version
       ...
    else:
       # start non-GUI version
       ...
    return app.exec_()
//! [0]


//! [1]
QApplication.setStyle(QWindowsStyle())
//! [1]


//! [2]
def main():
    QApplication.setColorSpec(QApplication.ManyColor)
    QApplication app(sys.argv)
    ...
    return app.exec_()

//! [2]


//! [3]
class MyWidget (QWidget):
    # ...
    def sizeHint(self):
        return QSize(80, 25).expandedTo(QApplication.globalStrut())
//! [3]


//! [4]
def showAllHiddenTopLevelWidgets():
    for widget in QApplication.topLevelWidgets():
        if widget.isHidden():
            widget.show()
//! [4]


//! [5]
def updateAllWidgets():
    for widget in QApplication.allWidgets()
        widget.update()
//! [5]


//! [6]
if __name__ == '__main__':
    QApplication.setDesktopSettingsAware(False)
    app = QApplication(sys.argv)
    # ...
    return app.exec_()
//! [6]


//! [7]
if (startPos - currentPos).manhattanLength() >= QApplication.startDragDistance():
    startTheDrag()
//! [7]


//! [8]
class MyApplication (QApplication):
# ...
    def commitData(QSessionManager& manager)
        if manager.allowsInteraction():
            ret = QMessageBox.warning(
                    mainWindow,
                    QObject.tr("My Application"),
                    QObject.tr("Save changes to document?"),
                    QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel)

            if ret == QMessageBox.Save:
                manager.release()
                if not saveDocument():
                    manager.cancel()
            elif ret == QMessageBox.Discard:
                pass
            else:
                manager.cancel()
        else:
            # we did not get permission to interact, then
            # do something reasonable instead
            pass
//! [8]


//! [9]
appname -session id
//! [9]


//! [10]
for command in mySession.restartCommand():
    do_something(command)
//! [10]


//! [11]
for command in mySession.discardCommand():
    do_something(command)
//! [11]


//! [12]
widget = qApp.widgetAt(x, y)
if widget:
    widget = widget.window()
//! [12]


//! [13]
widget = qApp.widgetAt(point)
if widget:
    widget = widget.window()
//! [13]
