/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0] //! [1]
def __init__(self, parent):
    QWizard.__init__(self, parent):
    self.addPage(IntroPage())
    self.addPage(ClassInfoPage())
    self.addPage(CodeStylePage())
    self.addPage(OutputFilesPage())
    self.addPage(ConclusionPage())
//! [0]

    self.setPixmap(QWizard.BannerPixmap, QPixmap(":/images/banner.png"))
    self.setPixmap(QWizard.BackgroundPixmap, QPixmap(":/images/background.png"))

    self.setWindowTitle(self.tr("Class Wizard"))
//! [2]

//! [1] //! [2]

//! [3]
def accept(self):
//! [3] //! [4]
    className = self.field("className").toByteArray()
    baseClass = self.field("baseClass").toByteArray()
    macroName = self.field("macroName").toByteArray()
    baseInclude = self.field("baseInclude").toByteArray()

    outputDir = self.field("outputDir").toString()
    header = self.field("header").toString()
    implementation = self.field("implementation").toString()
//! [4]

...

//! [5]
    QDialog.accept(self)
//! [5] //! [6]
}
//! [6]

//! [7]
class IntroPage (QWizardPage):

    def __init__(self, parent):
        QWizardPage.__init__(self, parent)

        self.setTitle(tr("Introduction"))
        self.setPixmap(QWizard.WatermarkPixmap, QPixmap(":/images/watermark1.png"))

        label = QLabel(self.tr("This wizard will generate a skeleton C++ class " \
                                    "definition, including a few functions. You simply " \
                                    "need to specify the class name and set a few " \
                                    "options to produce a header file and an " \
                                    "implementation file for your new C++ class."))
        label.setWordWrap(True)

        layout = QVBoxLayout()
        layout.addWidget(label)
        self.setLayout(layout)
}
//! [7]

//! [8] //! [9]
class ClassInfoPage(QWizardPage):

    def __init__(self, parent):
        QWizardPage.__init__(self, parent)
//! [8]
        self.setTitle(self.tr("Class Information"))
        self.setSubTitle(self.tr("Specify basic information about the class for which you " \
                                 "want to generate skeleton source code files."))
        self.setPixmap(QWizard.LogoPixmap, QPixmap(":/images/logo1.png"))

//! [10]
        classNameLabel = QLabel(self.tr("&Class name:"))
        classNameLineEdit = QLineEdit()
        classNameLabel.setBuddy(classNameLineEdit)

        baseClassLabel = QLabel(self.tr("B&ase class:"))
        baseClassLineEdit = QLineEdit()
        baseClassLabel.setBuddy(baseClassLineEdit)

        qobjectMacroCheckBox = QCheckBox(self.tr("Generate Q_OBJECT &macro"))

//! [10]
        groupBox = QGroupBox(self.tr("C&onstructor"))
//! [9]

        qobjectCtorRadioButton = QRadioButton(self.tr("&QObject-style constructor"))
        qwidgetCtorRadioButton = QRadioButton(self.tr("Q&Widget-style constructor"))
        defaultCtorRadioButton = QRadioButton(self.tr("&Default constructor"))
        copyCtorCheckBox = QCheckBox(self.tr("&Generate copy constructor and operator="))

        defaultCtorRadioButton.setChecked(True)

        self.connect(defaultCtorRadioButton, SIGNAL("toggled(bool)"),
                copyCtorCheckBox, SLOT("setEnabled(bool)"))

//! [11] //! [12]
        registerField("className*", classNameLineEdit)
        registerField("baseClass", baseClassLineEdit)
        registerField("qobjectMacro", qobjectMacroCheckBox)
//! [11]
        registerField("qobjectCtor", qobjectCtorRadioButton)
        registerField("qwidgetCtor", qwidgetCtorRadioButton)
        registerField("defaultCtor", defaultCtorRadioButton)
        registerField("copyCtor", copyCtorCheckBox)

        groupBoxLayout = QVBoxLayout()
//! [12]
        groupBoxLayout.addWidget(qobjectCtorRadioButton)
        groupBoxLayout.addWidget(qwidgetCtorRadioButton)
        groupBoxLayout.addWidget(defaultCtorRadioButton)
        groupBoxLayout.addWidget(copyCtorCheckBox)
        groupBox.setLayout(groupBoxLayout)

        layout = QGridLayout()
        layout.addWidget(classNameLabel, 0, 0)
        layout.addWidget(classNameLineEdit, 0, 1)
        layout.addWidget(baseClassLabel, 1, 0)
        layout.addWidget(baseClassLineEdit, 1, 1)
        layout.addWidget(qobjectMacroCheckBox, 2, 0, 1, 2)
        layout.addWidget(groupBox, 3, 0, 1, 2)
        self.setLayout(layout)
//! [13]

//! [13]

//! [14]
class CodeStylePage(QWizardPage):

    def __init__(self, parent):
        QWizardPage.__init__(self, parent)
        self.setTitle(tr("Code Style Options"))
        self.setSubTitle(tr("Choose the formatting of the generated code."))
        self.setPixmap(QWizard.LogoPixmap, QPixmap(":/images/logo2.png"))

        commentCheckBox = QCheckBox(self.tr("&Start generated files with a comment"))
//! [14]
        commentCheckBox.setChecked(True)

        protectCheckBox = QCheckBox(self.tr("&Protect header file against multiple " \
                                        "inclusions"))
        protectCheckBox.setChecked(True)

        macroNameLabel = QLabel(self.tr("&Macro name:"))
        macroNameLineEdit = QLineEdit()
        macroNameLabel.setBuddy(macroNameLineEdit)

        includeBaseCheckBox = QCheckBox(self.tr("&Include base class definition"))
        baseIncludeLabel = QLabel(self.tr("Base class include:"))
        baseIncludeLineEdit = QLineEdit()
        baseIncludeLabel.setBuddy(baseIncludeLineEdit)

        self.connect(protectCheckBox, SIGNAL("toggled(bool)"),
                    macroNameLabel, SLOT("setEnabled(bool)"))
        self.connect(protectCheckBox, SIGNAL("toggled(bool)"),
                    macroNameLineEdit, SLOT("setEnabled(bool)"))
        self.connect(includeBaseCheckBox, SIGNAL("toggled(bool)"),
                    baseIncludeLabel, SLOT("setEnabled(bool)"))
        self.connect(includeBaseCheckBox, SIGNAL(toggled(bool)),
                    baseIncludeLineEdit, SLOT("setEnabled(bool)"))

        self.registerField("comment", commentCheckBox)
        self.registerField("protect", protectCheckBox)
        self.registerField("macroName", macroNameLineEdit)
        self.registerField("includeBase", includeBaseCheckBox)
        self.registerField("baseInclude", baseIncludeLineEdit)

        layout = QGridLayout()
        layout.setColumnMinimumWidth(0, 20)
        layout.addWidget(commentCheckBox, 0, 0, 1, 3)
        layout.addWidget(protectCheckBox, 1, 0, 1, 3)
        layout.addWidget(macroNameLabel, 2, 1)
        layout.addWidget(macroNameLineEdit, 2, 2)
        layout.addWidget(includeBaseCheckBox, 3, 0, 1, 3)
        layout.addWidget(baseIncludeLabel, 4, 1)
        layout.addWidget(baseIncludeLineEdit, 4, 2)
//! [15]
        self.setLayout(layout)
}
//! [15]

//! [16]
    def initializePage(self):
        className = self.field("className").toString()
        self.macroNameLineEdit.setText(className.toUpper() + "_H")

        baseClass = self.field("baseClass").toString()

        self.includeBaseCheckBox.setChecked(not baseClass.isEmpty())
        self.includeBaseCheckBox.setEnabled(not baseClass.isEmpty())
        self.baseIncludeLabel.setEnabled(not baseClass.isEmpty())
        self.baseIncludeLineEdit.setEnabled(not baseClass.isEmpty())

        if baseClass.isEmpty():
            self.baseIncludeLineEdit.clear()
        elsif QRegExp("Q[A-Z].*").exactMatch(baseClass):
            baseIncludeLineEdit.setText("<" + baseClass + ">")
        else:
            baseIncludeLineEdit.setText("\"" + baseClass.toLower() + ".h\"")
//! [16]

//! [17]
    def initializePage(self):
        className = field("className").toString()
        self.headerLineEdit.setText(className.toLower() + ".h")
        self.implementationLineEdit.setText(className.toLower() + ".cpp")
        self.outputDirLineEdit.setText(QDir.convertSeparators(QDir.tempPath()))
//! [17]
