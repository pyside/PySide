/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QBuffer>
#include <QPalette>

static void main_snippet()
{
//! [0]
    buffer = QBuffer()

    buffer.open(QBuffer.ReadWrite)
    buffer.write("Qt rocks!")
    buffer.seek(0)
    ch = buffer.getChar()  # ch == 'Q'
    ch = buffer.getChar()  # ch == 't'
    ch = buffer.getChar()  # ch == ' '
    ch = buffer.getChar()  # ch == 'r'
//! [0]
}

static void write_datastream_snippets()
{
//! [1]
    byteArray = QByteArray()
    buffer = QBuffer(byteArray)
    buffer.open(QIODevice.WriteOnly)

    out = QDataStream(buffer)
    out << QApplication.palette()
//! [1]
}

static void read_datastream_snippets()
{
    QByteArray byteArray;

//! [2]
    palette = QPalette()
    buffer = QBuffer(byteArray)
    buffer.open(QIODevice.ReadOnly)

    in = QDataStream(buffer)
    in >> palette
//! [2]
}

static void bytearray_ptr_ctor_snippet()
{
//! [3]
    byteArray = QByteArray("abc")
    buffer = QBuffer(byteArray)
    buffer.open(QIODevice.WriteOnly)
    buffer.seek(3)
    buffer.write("def")
    buffer.close()
    # byteArray == "abcdef"
//! [3]
}

static void setBuffer_snippet()
{
//! [4]
    byteArray = QByteArray("abc")
    buffer = QBuffer()
    buffer.setBuffer(byteArray)
    buffer.open(QIODevice.WriteOnly)
    buffer.seek(3)
    buffer.write("def")
    buffer.close()
    # byteArray == "abcdef"
//! [4]
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    main_snippet();
    bytearray_ptr_ctor_snippet();
    write_datastream_snippets();
    read_datastream_snippets();
    setBuffer_snippet();
    return 0;
}
