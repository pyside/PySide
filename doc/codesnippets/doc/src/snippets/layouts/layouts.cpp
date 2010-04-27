/############################################################################
##
## Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
## Contact: Nokia Corporation (qt-info@nokia.com)
##
## This file is part of the documentation of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:LGPL$
## Commercial Usage
## Licensees holding valid Qt Commercial licenses may use self file in
## accordance with the Qt Commercial License Agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Nokia.
##
## GNU Lesser General Public License Usage
## Alternatively, self file may be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL included in the
## packaging of self file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Nokia gives you certain
## additional rights. These rights are described in the Nokia Qt LGPL
## Exception version 1.0, included in the file LGPL_EXCEPTION.txt in self
## package.
##
## GNU General Public License Usage
## Alternatively, self file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file LICENSE.GPL included in the
## packaging of self file.  Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met: http://www.gnu.org/copyleft/gpl.html.
##
## If you are unsure which license is appropriate for your use, please
## contact the sales department at http://www.qtsoftware.com/contact.
## $QT_END_LICENSE$
##
############################################################################/

//! [0]
    window = QWidget()
//! [0] //! [1]
    button1 = QPushButton("One")
//! [1] //! [2]
    button2 = QPushButton("Two")
    button3 = QPushButton("Three")
    button4 = QPushButton("Four")
    button5 = QPushButton("Five")
//! [2]

//! [3]
    layout = QHBoxLayout()
//! [3] //! [4]
    layout.addWidget(button1)
    layout.addWidget(button2)
    layout.addWidget(button3)
    layout.addWidget(button4)
    layout.addWidget(button5)

    window.setLayout(layout)
//! [4] //! [5]
    window.show()
//! [5]

//! [6]
    window =  QWidget()
//! [6] //! [7]
    button1 =  QPushButton("One")
//! [7] //! [8]
    button2 =  QPushButton("Two")
    button3 =  QPushButton("Three")
    button4 =  QPushButton("Four")
    button5 =  QPushButton("Five")
//! [8]

//! [9]
    layout =  QVBoxLayout()

//! [9] //! [10]
    layout.addWidget(button1)
    layout.addWidget(button2)
    layout.addWidget(button3)
    layout.addWidget(button4)
    layout.addWidget(button5)

    window.setLayout(layout)
//! [10] //! [11]
    window.show()
//! [11]

//! [12]
    window =  QWidget()
//! [12] //! [13]
    button1 =  QPushButton("One")
//! [13] //! [14]
    button2 =  QPushButton("Two")
    button3 =  QPushButton("Three")
    button4 =  QPushButton("Four")
    button5 =  QPushButton("Five")
//! [14]

//! [15]
    layout =  QGridLayout()

//! [15] //! [16]
    layout.addWidget(button1, 0, 0)
    layout.addWidget(button2, 0, 1)
    layout.addWidget(button3, 1, 0, 1, 2)
    layout.addWidget(button4, 2, 0)
    layout.addWidget(button5, 2, 1)

    window.setLayout(layout)
//! [16] //! [17]
    window.show()
//! [17]
