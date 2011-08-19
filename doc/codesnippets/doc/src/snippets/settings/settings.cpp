/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
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

#include <QtGui>

QWidget *win
QWidget *panel

void snippet_ctor1()
{
//! [0]
    settings = QSettings("MySoft", "Star Runner")
//! [0]
}

void snippet_ctor2()
{
//! [1]
    QCoreApplication.setOrganizationName("MySoft")
//! [1] //! [2]
    QCoreApplication.setOrganizationDomain("mysoft.com")
//! [2] //! [3]
    QCoreApplication.setApplicationName("Star Runner")
//! [3]

//! [4]
    settings = QSettings()
//! [4]

//! [5]
    settings.setValue("editor/wrapMargin", 68)
//! [5] //! [6]
    margin = int(settings.value("editor/wrapMargin"))
//! [6]
    {
//! [7]
    margin = int(settings.value("editor/wrapMargin", 80))
//! [7]
    }

//! [8]
    settings.setValue("mainwindow/size", win.size())
//! [8] //! [9]
    settings.setValue("mainwindow/fullScreen", win.isFullScreen())
//! [9] //! [10]
    settings.setValue("outputpanel/visible", panel.isVisible())
//! [10]

//! [11]
    settings.beginGroup("mainwindow")
    settings.setValue("size", win.size())
    settings.setValue("fullScreen", win.isFullScreen())
    settings.endGroup()
//! [11]

//! [12]
    settings.beginGroup("outputpanel")
    settings.setValue("visible", panel.isVisible())
    settings.endGroup()
//! [12]
}

void snippet_locations()
{
//! [13]
    obj1 = QSettings("MySoft", "Star Runner")
//! [13] //! [14]
    obj2 = QSettings("MySoft")
    obj3 = QSettings(QSettings.SystemScope, "MySoft", "Star Runner")
    obj4 = QSettings(QSettings.SystemScope, "MySoft")
//! [14]

    {
//! [15]
    settings = QSettings(QSettings.IniFormat, QSettings.UserScope,
                         "MySoft", "Star Runner")
//! [15]
    }

    {
    QSettings settings("starrunner.ini", QSettings.IniFormat)
    }

    {
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft",
                       QSettings.NativeFormat)
    }
}

class MainWindow : public QMainWindow
{
public:
    MainWindow()

    void writeSettings()
    void readSettings()

protected:
    void closeEvent(QCloseEvent *event)
}

//! [16]
class MainWindow(QMainWindow):
    ...
    def writeSettings(self):
        self.settings = QSettings("Moose Soft", "Clipper")
        self.settings.beginGroup("MainWindow")
        self.settings.setValue("size", self.size())
        self.settings.setValue("pos", self.pos())
        self.settings.endGroup()
//! [16]

//! [17]
    def readSettings(self):
        self.settings = QSettings("Moose Soft", "Clipper")
        self.settings.beginGroup("MainWindow")
        self.resize(settings.value("size", QSize(400, 400)).toSize())
        self.move(settings.value("pos", QPoint(200, 200)).toPoint())
        self.settings.endGroup()
//! [17]

//! [18]
    def __init__(self):
        self.settings = None
//! [18] //! [19]
        self.readSettings()
//! [19] //! [20]

//! [20]

bool userReallyWantsToQuit() { return true; }

//! [21]
    # event : QCloseEvent
    def closeEvent(self, event):
        if self.userReallyWantsToQuit():
            self.writeSettings()
            event.accept()
        else:
            event.ignore()
//! [21]
