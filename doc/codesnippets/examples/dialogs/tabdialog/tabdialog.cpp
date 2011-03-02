
//! [0]
class TabDialog (QDialog):
    def __init__(self, fileName, parent = None):
        QDialog.__init__(self, parent)
        fileInfo = QFileInfo(fileName)

        self.tabWidget = QTabWidget()
        self.tabWidget.addTab(GeneralTab(fileInfo), "General")
        self.tabWidget.addTab(PermissionsTab(fileInfo), "Permissions")
        self.tabWidget.addTab(ApplicationsTab(fileInfo), "Applications")
//! [0]

//! [1] //! [2]
        self.buttonBox = QDialogButtonBox(QDialogButtonBox.Ok
//! [1] //! [3]
                                     | QDialogButtonBox.Cancel)

        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)
//! [2] //! [3]

//! [4]
        mainLayout = QVBoxLayout()
        mainLayout.addWidget(tabWidget)
        mainLayout.addWidget(buttonBox)
        self.setLayout(mainLayout)
//! [4]

//! [5]
        self.setWindowTitle("Tab Dialog")
//! [5]

//! [6]
class GeneralTab (QWidget):
    def __init__(self, fileInfo, parent = None):
        QWidget.__init__(self, parent)
        fileNameLabel = QLabel("File Name:")
        fileNameEdit = QLineEdit(fileInfo.fileName())

        pathLabel = QLabel("Path:")
        pathValueLabel = QLabel(fileInfo.absoluteFilePath())
        pathValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        sizeLabel = QLabel("Size:")
        size = fileInfo.size()/1024
        sizeValueLabel = QLabel("%d K" % size)
        sizeValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        lastReadLabel = QLabel("Last Read:")
        lastReadValueLabel = QLabel(fileInfo.lastRead().toString())
        lastReadValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        lastModLabel = QLabel("Last Modified:")
        lastModValueLabel = QLabel(fileInfo.lastModified().toString())
        lastModValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        mainLayout = QVBoxLayout()
        mainLayout.addWidget(fileNameLabel)
        mainLayout.addWidget(fileNameEdit)
        mainLayout.addWidget(pathLabel)
        mainLayout.addWidget(pathValueLabel)
        mainLayout.addWidget(sizeLabel)
        mainLayout.addWidget(sizeValueLabel)
        mainLayout.addWidget(lastReadLabel)
        mainLayout.addWidget(lastReadValueLabel)
        mainLayout.addWidget(lastModLabel)
        mainLayout.addWidget(lastModValueLabel)
        mainLayout.addStretch(1)
        self.setLayout(mainLayout)
//! [6]

//! [7]
class PermissionsTab (QWidget):
    def __init__(self, fileInfo, parent = None):
        QWidget.__init__(self, parent)
        permissionsGroup = QGroupBox("Permissions")

        readable = QCheckBox("Readable")
        if fileInfo.isReadable():
            readable.setChecked(True)

        writable = QCheckBox("Writable")
        if fileInfo.isWritable():
            writable.setChecked(True)

        executable = QCheckBox("Executable")
        if fileInfo.isExecutable():
            executable.setChecked(True)

        ownerGroup = QGroupBox("Ownership")

        ownerLabel = QLabel("Owner")
        ownerValueLabel = QLabel(fileInfo.owner())
        ownerValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        groupLabel = QLabel("Group")
        groupValueLabel = QLabel(fileInfo.group())
        groupValueLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        permissionsLayout = QVBoxLayout()
        permissionsLayout.addWidget(readable)
        permissionsLayout.addWidget(writable)
        permissionsLayout.addWidget(executable)
        permissionsGroup.setLayout(permissionsLayout)

        ownerLayout = QVBoxLayout()
        ownerLayout.addWidget(ownerLabel)
        ownerLayout.addWidget(ownerValueLabel)
        ownerLayout.addWidget(groupLabel)
        ownerLayout.addWidget(groupValueLabel)
        ownerGroup.setLayout(ownerLayout)

        mainLayout = QVBoxLayout()
        mainLayout.addWidget(permissionsGroup)
        mainLayout.addWidget(ownerGroup)
        mainLayout.addStretch(1)
        self.setLayout(mainLayout)
//! [7]

//! [8]
class ApplicationsTab (QWidget):
    def __init__(self, fileInfo, parent = None):
        QWidget.__init__(self, parent)
        topLabel = QLabel("Open with:")

        applicationsListBox = QListWidget()
        applications = []

        for i in range(30):
            applications.append("Application %d" %s i)
        applicationsListBox.insertItems(0, applications)

        if fileInfo.suffix().isEmpty():
            alwaysCheckBox = QCheckBox("Always use this application to open this type of file")
        else:
            alwaysCheckBox = QCheckBox("Always use this application to open files with the extension '%s'" % fileInfo.suffix())

        layout = QVBoxLayout()
        layout.addWidget(topLabel)
        layout.addWidget(applicationsListBox)
        layout.addWidget(alwaysCheckBox)
        self.setLayout(layout)
//! [8]
