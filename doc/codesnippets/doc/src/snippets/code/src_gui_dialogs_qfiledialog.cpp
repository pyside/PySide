//! [0]
fileName, filter = QFileDialog.getOpenFileName(self,
    "Open Image", "/home/jana", "Image Files (*.png *.jpg *.bmp)")
//! [0]


//! [1]
"Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"
//! [1]


//! [2]
dialog = QFileDialog(self)
dialog.setFileMode(QFileDialog.AnyFile)
//! [2]


//! [3]
dialog.setNameFilter("Images (*.png *.xpm *.jpg)")
//! [3]


//! [4]
dialog.setViewMode(QFileDialog.Detail)
//! [4]


//! [5]
if dialog.exec_():
    fileNames = dialog.selectedFiles()
//! [5]


//! [6]
dialog.setNameFilter("All C++ files (*.cpp *.cc *.C *.cxx *.c++)")
dialog.setNameFilter("*.cpp *.cc *.C *.cxx *.c++")
//! [6]


//! [7]
filters = QStringList()
filters << "Image files (*.png *.xpm *.jpg)"
        << "Text files (*.txt)"
        << "Any files (*)"

dialog = QFileDialog(this)
dialog.setNameFilters(filters)
dialog.exec_()
//! [7]


//! [8]
fileName, filter = QFileDialog.getOpenFileName(self, "Open File",
                                       "/home",
                                       "Images (*.png *.xpm *.jpg)")
//! [8]


//! [9]
files, filter = QFileDialog.getOpenFileNames(self,
                                     "Select one or more files to open",
                                     "/home",
                                     "Images (*.png *.xpm *.jpg)")
//! [9]


//! [10]
for it in list:
    myProcessing(it)
    it++
//! [10]


//! [11]
fileName, filter = QFileDialog.getSaveFileName(self, "Save F:xile",
                                       "/home/jana/untitled.png",
                                       "Images (*.png *.xpm *.jpg)")
//! [11]


//! [12]
dir = QFileDialog.getExistingDirectory(self, "Open Directory",
                                       "/home",
                                       QFileDialog.ShowDirsOnly
                                       | QFileDialog.DontResolveSymlinks)
//! [12]
