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

//! [0]
def paintEvent(self, qpaintevent):
    option = QStyleOptionButton()
    option.initFrom(self)
    if isDown():
        option.state = QStyle.State_Sunken
    else:
        option.state = QStyle.State_Raised

    if self.isDefault():
        option.features = option.features or QStyleOptionButton.DefaultButton
    option.text = self.text()
    option.icon = self.icon()

    painter = QPainter(self)
    self.style().drawControl(QStyle.CE_PushButton, option, painter, self)
//! [0]
//! [1]
    option = QStyleOptionFrame()

    if isinstance(option, QStyleOptionFrameV2):
        frameOptionV2 = QStyleOptionFrameV2(option)

        # draw the frame using frameOptionV2

//! [1]

//! [2]
    if isinstance(option, QStyleOptionProgressBarV2):
        progressBarV2 = QStyleOptionProgressBarV2(option)

        # draw the progress bar using progressBarV2

//! [2]

//! [3]
    if isinstance(option, QStyleOptionTabV2):
        tabV2 = QStyleOptionTabV2(option)

        # draw the tab using tabV2

//! [3]


//! [4]
def drawPrimitive(self, element, option, painter, widget):
    if element == self.PE_FrameFocusRect:
        focusRectOption =  QStyleOptionFocusRect(option)
        if focusRectOption:
            # ...


    # ...

//! [4]
