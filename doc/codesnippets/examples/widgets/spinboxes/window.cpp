######################################
#
# Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
# Contact: Qt Software Information (qt-info@nokia.com)
#
# This file is part of the example classes of the Qt Toolkit.
#
# $QT_BEGIN_LICENSE:LGPL$
# Commercial Usage
# Licensees holding valid Qt Commercial licenses may use self file in
# accordance with the Qt Commercial License Agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and Nokia.
#
# GNU Lesser General Public License Usage
# Alternatively, self file may be used under the terms of the GNU Lesser
# General Public License version 2.1 as published by the Free Software
# Foundation and appearing in the file LICENSE.LGPL included in the
# packaging of self file.  Please review the following information to
# ensure the GNU Lesser General Public License version 2.1 requirements
# will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#
# In addition, as a special exception, Nokia gives you certain
# additional rights. These rights are described in the Nokia Qt LGPL
# Exception version 1.0, included in the file LGPL_EXCEPTION.txt in self
# package.
#
# GNU General Public License Usage
# Alternatively, self file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of self file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl.html.
#
# If you are unsure which license is appropriate for your use, please
# contact the sales department at qt-sales@nokia.com.
# $QT_END_LICENSE$
#
######################################

from PySide.QtGui import *

//! [0]
def __init__(self):
    createSpinBoxes()
    createDateTimeEdits()
    createDoubleSpinBoxes()

    layout =  QHBoxLayout()
    layout.addWidget(spinBoxesGroup)
    layout.addWidget(editsGroup)
    layout.addWidget(doubleSpinBoxesGroup)
    setLayout(layout)

    setWindowTitle(tr("Spin Boxes"))
//! [0]

//! [1]
def createSpinBoxes(self):
    spinBoxesGroup =  QGroupBox(tr("Spinboxes"))

    integerLabel = QLabel(tr("Enter a value between "
                             "%1 and %2:").arg(-20).arg(20))
    integerSpinBox = QSpinBox()
    integerSpinBox.setRange(-20, 20)
    integerSpinBox.setSingleStep(1)
    integerSpinBox.setValue(0)
//! [1]

//! [2]
    zoomLabel = QLabel(tr("Enter a zoom value between "
                          "%1 and %2:").arg(0).arg(1000))
//! [3]
    zoomSpinBox =  QSpinBox()
    zoomSpinBox.setRange(0, 1000)
    zoomSpinBox.setSingleStep(10)
    zoomSpinBox.setSuffix("%")
    zoomSpinBox.setSpecialValueText(tr("Automatic"))
    zoomSpinBox.setValue(100)
//! [2] //! [3]

//! [4]
    priceLabel = QLabel(tr("Enter a price between "
                           "%1 and %2:").arg(0).arg(999))
    priceSpinBox = QSpinBox()
    priceSpinBox.setRange(0, 999)
    priceSpinBox.setSingleStep(1)
    priceSpinBox.setPrefix("$")
    priceSpinBox.setValue(99)
//! [4] //! [5]

    spinBoxLayout =  QVBoxLayout()
    spinBoxLayout.addWidget(integerLabel)
    spinBoxLayout.addWidget(integerSpinBox)
    spinBoxLayout.addWidget(zoomLabel)
    spinBoxLayout.addWidget(zoomSpinBox)
    spinBoxLayout.addWidget(priceLabel)
    spinBoxLayout.addWidget(priceSpinBox)
    spinBoxesGroup.setLayout(spinBoxLayout)

//! [5]

//! [6]
def createDateTimeEdits(self):
    editsGroup =  QGroupBox(tr("Date and time spin boxes"))

    dateLabel = QLabel()
    dateEdit = QDateEdit(QDate.currentDate())
    dateEdit.setDateRange(QDate(2005, 1, 1), QDate(2010, 12, 31))
    dateLabel.setText(tr("Appointment date (between %0 and %1):")
                       .arg(dateEdit.minimumDate().toString(Qt.ISODate))
                       .arg(dateEdit.maximumDate().toString(Qt.ISODate)))
//! [6]

//! [7]
    timeLabel =  QLabel()
    timeEdit =  QTimeEdit(QTime.currentTime())
    timeEdit.setTimeRange(QTime(9, 0, 0, 0), QTime(16, 30, 0, 0))
    timeLabel.setText(tr("Appointment time (between %0 and %1):")
                       .arg(timeEdit.minimumTime().toString(Qt.ISODate))
                       .arg(timeEdit.maximumTime().toString(Qt.ISODate)))
//! [7]

//! [8]
    meetingLabel = QLabel()
    meetingEdit = QDateTimeEdit(QDateTime.currentDateTime())
//! [8]

//! [9]
    formatLabel = QLabel(tr("Format string for the meeting date "
                            "and time:"))
    formatComboBox = QComboBox()
    formatComboBox.addItem("yyyy-MM-dd hh:mm:ss (zzz 'ms')")
    formatComboBox.addItem("hh:mm:ss MM/dd/yyyy")
    formatComboBox.addItem("hh:mm:ss dd/MM/yyyy")
    formatComboBox.addItem("hh:mm:ss")
    formatComboBox.addItem("hh:mm ap")
//! [9] //! [10]

    connect(formatComboBox, SIGNAL("activated(const QString &)"),
            self, SLOT("setFormatString(const QString &)"))
//! [10]

    setFormatString(formatComboBox.currentText())

//! [11]
    editsLayout = QVBoxLayout()
    editsLayout.addWidget(dateLabel)
    editsLayout.addWidget(dateEdit)
    editsLayout.addWidget(timeLabel)
    editsLayout.addWidget(timeEdit)
    editsLayout.addWidget(meetingLabel)
    editsLayout.addWidget(meetingEdit)
    editsLayout.addWidget(formatLabel)
    editsLayout.addWidget(formatComboBox)
    editsGroup.setLayout(editsLayout)
//! [11]

//! [12]
def setFormatString(self, formatString):
    meetingEdit.setDisplayFormat(formatString)
//! [12] //! [13]
    if meetingEdit.displayedSections() & QDateTimeEdit.DateSections_Mask:
        meetingEdit.setDateRange(QDate(2004, 11, 1), QDate(2005, 11, 30))
        meetingLabel.setText(tr("Meeting date (between %0 and %1):")
            .arg(meetingEdit.minimumDate().toString(Qt.ISODate))
	    .arg(meetingEdit.maximumDate().toString(Qt.ISODate)))
    else:
        meetingEdit.setTimeRange(QTime(0, 7, 20, 0), QTime(21, 0, 0, 0))
        meetingLabel.setText(tr("Meeting time (between %0 and %1):")
            .arg(meetingEdit.minimumTime().toString(Qt.ISODate))
	    .arg(meetingEdit.maximumTime().toString(Qt.ISODate)))
//! [13]

//! [14]
def createDoubleSpinBoxes():
    doubleSpinBoxesGroup =  QGroupBox(tr("Double precision spinboxes"))

    precisionLabel = QLabel(tr("Number of decimal places "
                               "to show:"))
    precisionSpinBox = QSpinBox()
    precisionSpinBox.setRange(0, 100)
    precisionSpinBox.setValue(2)
//! [14]

//! [15]
    doubleLabel = QLabel(tr("Enter a value between "
                            "%1 and %2:").arg(-20).arg(20))
    doubleSpinBox =  QDoubleSpinBox ()
    doubleSpinBox.setRange(-20.0, 20.0)
    doubleSpinBox.setSingleStep(1.0)
    doubleSpinBox.setValue(0.0)
//! [15]

//! [16]
    scaleLabel = QLabel(tr("Enter a scale factor between "
                           "%1 and %2:").arg(0).arg(1000.0))
    scaleSpinBox =  QDoubleSpinBox()
    scaleSpinBox.setRange(0.0, 1000.0)
    scaleSpinBox.setSingleStep(10.0)
    scaleSpinBox.setSuffix("%")
    scaleSpinBox.setSpecialValueText(tr("No scaling"))
    scaleSpinBox.setValue(100.0)
//! [16]

//! [17]
    priceLabel = QLabel(tr("Enter a price between "
                           "%1 and %2:").arg(0).arg(1000))
    priceSpinBox = QDoubleSpinBox()
    priceSpinBox.setRange(0.0, 1000.0)
    priceSpinBox.setSingleStep(1.0)
    priceSpinBox.setPrefix("$")
    priceSpinBox.setValue(99.99)

    connect(precisionSpinBox, SIGNAL("valueChanged(int)"),
//! [17]
            self, SLOT("changePrecision(int))")

//! [18]
    spinBoxLayout =  QVBoxLayout()
    spinBoxLayout.addWidget(precisionLabel)
    spinBoxLayout.addWidget(precisionSpinBox)
    spinBoxLayout.addWidget(doubleLabel)
    spinBoxLayout.addWidget(doubleSpinBox)
    spinBoxLayout.addWidget(scaleLabel)
    spinBoxLayout.addWidget(scaleSpinBox)
    spinBoxLayout.addWidget(priceLabel)
    spinBoxLayout.addWidget(priceSpinBox)
    doubleSpinBoxesGroup.setLayout(spinBoxLayout)
}
//! [18]

//! [19]
def changePrecision(self, int)
    doubleSpinBox.setDecimals(decimals)
    scaleSpinBox.setDecimals(decimals)
    priceSpinBox.setDecimals(decimals)

//! [19]
