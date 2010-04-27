//! [0]
ret = QMessageBox.warning(self, self.tr("My Application"),
                               self.tr("The document has been modified.\n" + \
                                  "Do you want to save your changes?"),
                               QMessageBox.Save | QMessageBox.Discard
                               | QMessageBox.Cancel,
                               QMessageBox.Save)
//! [0]


//! [1]
msgBox = QMessageBox()
msgBox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
result = msgBox.exec_()

if result == QMessageBox.Yes:
    # yes was clicked
elif result == QMessageBox.No:
    # no was clicked
else:
    # should never be reached
//! [1]


//! [2]
msgBox = QMessageBox()
connectButton = msgBox.addButton(self.tr("Connect"), QMessageBox.ActionRole)
abortButton = msgBox.addButton(QMessageBox.Abort)

msgBox.exec_()

if msgBox.clickedButton() == connectButton:
    # connect
elif msgBox.clickedButton() == abortButton:
    # abort
}
//! [2]


//! [3]
messageBox = QMessageBox(self)
disconnectButton = messageBox.addButton(self.tr("Disconnect"),
                                        QMessageBox.ActionRole)
...
messageBox.exec_()
if messageBox.clickedButton() == disconnectButton:
    ...

//! [3]


//! [4]
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
# Not Supported by PySide
    QT_REQUIRE_VERSION(argc, argv, "4.0.2")

    QApplication app(argc, argv);
    ...
    return app.exec();
}
//! [4]

//! [5]
msgBox = QMessageBox()
msgBox.setText("The document has been modified.")
msgBox.exec_()
//! [5]

//! [6]
msgBox = QMessageBox()
msgBox.setText("The document has been modified.")
msgBox.setInformativeText("Do you want to save your changes?")
msgBox.setStandardButtons(QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel)
msgBox.setDefaultButton(QMessageBox.Save)
ret = msgBox.exec_()
//! [6]

//! [7]

if ret == QMessageBox.Save:
    # Save was clicked
elif ret == QMessageBox.Discard:
    # Don't save was clicked
elif ret == QMessageBox.Cancel:
    # cancel was clicked
else:
    # should never be reached

//! [7]

//! [9]
msgBox = QMessageBox(self)
msgBox.setText(tr("The document has been modified.\n" + \
                  "Do you want to save your changes?"))
msgBox.setStandardButtons(QMessageBox.Save | QMessageBox.Discard
                          | QMessageBox.Cancel)
msgBox.setDefaultButton(QMessageBox.Save)
//! [9]
