
//! [implicit tr context]
def createMenus(self):
    fileMenu = menuBar().addMenu("&File")
//! [implicit tr context]

//! [0]
    fileToolBar = addToolBar("File")
    fileToolBar.addAction(newAct)
    fileToolBar.addAction(openAct)
//! [0]
