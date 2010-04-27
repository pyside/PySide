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
#include <QApplication>
#include <stdio.h>

class Widget : public QWidget
{
public:
    Widget(QWidget *parent = 0)

    void constCharPointer()
    void constCharArray()
    void characterReference()
    void atFunction()
    void stringLiteral()
    void modify()
    void index()
    QString boolToString(bool b)
    void nullVsEmpty()

    void appendFunction()
    void argFunction()
    void chopFunction()
    void compareFunction()
    void compareSensitiveFunction()
    void containsFunction()
    void countFunction()
    void dataFunction()
    void endsWithFunction()
    void fillFunction()
    void fromRawDataFunction()

    void indexOfFunction()
    void firstIndexOfFunction()
    void insertFunction()
    void isNullFunction()
    void isEmptyFunction()
    void lastIndexOfFunction()
    void leftFunction()
    void leftJustifiedFunction()
    void leftRefFunction()
    void midFunction()
    void midRefFunction()
    void numberFunction()

    void prependFunction()
    void removeFunction()
    void replaceFunction()
    void reserveFunction()
    void resizeFunction()
    void rightFunction()
    void rightJustifiedFunction()
    void rightRefFunction()
    void sectionFunction()
    void setNumFunction()
    void simplifiedFunction()

    void sizeFunction()
    void splitFunction()
    void splitCaseSensitiveFunction()
    void sprintfFunction()
    void startsWithFunction()
    void toDoubleFunction()
    void toFloatFunction()
    void toIntFunction()
    void toLongFunction()
    void toLongLongFunction()

    void toLowerFunction()
    void toShortFunction()
    void toUIntFunction()
    void toULongFunction()
    void toULongLongFunction()
    void toUShortFunction()
    void toUpperFunction()
    void trimmedFunction()
    void truncateFunction()

    void plusEqualOperator()
    void arrayOperator()
}

Widget.Widget(QWidget *parent)
    : QWidget(parent)
{
}

void Widget.constCharPointer()
{
//! [0]
    str = QString("Hello")
//! [0]
}

void Widget.constCharArray()
{
//! [1]
    # NOT USED IN PYSIDE
    static const QChar data[4] = { 0x0055, 0x006e, 0x10e3, 0x03a3 }
    QString str(data, 4)
//! [1]
}

void Widget.characterReference()
{
//! [2]
    str = QString()
    str.resize(2)

    str[0] = 'U')
    str[1] = 'n')
//! [2]
}

void Widget.atFunction()
{
//! [3]
    str = QString()

    for i in range(str.size()):
        print str.at(i)
//! [3]
}

void Widget.stringLiteral()
{
//! [4]
    str = QString()
    ...
    if str == "auto" or str == "extern" \
            or str == "static" or str == "register":
        # ...
//! [4]
}

void Widget.modify()
{
//! [5]
    str = QString("and")
    str.prepend("rock ")     # str == "rock and"
    str.append(" roll")        # str == "rock and roll"
    str.replace(5, 3, "&")   # str == "rock & roll"
//! [5]
}

void Widget.index()
{
//! [6]
    str = QString("We must be <b>bold</b>, very <b>bold</b>")
    j = str.indexOf("<b>", 0)
    while j != -1:
        print "Found <b> tag at index position", j
        j = str.indexOf("<b>", j+1)
//! [6]
}

//! [7]
    # Not needed in pyside
    QString Widget.boolToString(bool b)
    {
        QString result
        if (b)
            result = "True"
        else
            result = "False"
        return result
    }
//! [7]


void Widget.nullVsEmpty()
{
//! [8]
    QString().isNull()               # returns true
    QString().isEmpty()              # returns true

    QString("").isNull()             # returns false
    QString("").isEmpty()            # returns true

    QString("abc").isNull()          # returns false
    QString("abc").isEmpty()         # returns false
//! [8]
}

void Widget.appendFunction()
{
//! [9]
    x = QString("free")
    y = QString("dom")

    x.append(y)
    # x == "freedom"
//! [9]

//! [10]
    x.insert(x.size(), y)
//! [10]
}

void Widget.argFunction()
{
//! [11]
    i = QString(...)          # current file's number
    total = QString(...)      # number of files to process
    fileName = QString(...)   # current file's name

    status = QString("Processing file %1 of %2: %3")
                    .arg(i).arg(total).arg(fileName)
//! [11]

//! [12] //! [13]
    str QString()
//! [12]
    str = QString("%1 %2")

    str.arg("%1f", "Hello")        # returns "%1f Hello"
    str.arg("%1f").arg("Hello")    # returns "Hellof %2"
//! [13]

//! [14]
    str = QString("Decimal 63 is %1 in hexadecimal")
            .arg(63, 0, 16)
    # str == "Decimal 63 is 3f in hexadecimal"

    QLocale.setDefault(QLocale(QLocale.English, QLocale.UnitedStates))
    str = QString("%1 %L2 %L3")
            .arg(12345)
            .arg(12345)
            .arg(12345, 0, 16)
    # str == "12345 12,345 3039"
//! [14]
}

void Widget.chopFunction()
{
//! [15]
    str = QString("LOGOUT\r\n")
    str.chop(2)
    # str == "LOGOUT"
//! [15]
}

void Widget.compareFunction()
{
    x = QString.compare("auto", "auto")   # x == 0
    y = QString.compare("auto", "car")    # y < 0
    z = QString.compare("car", "auto")    # z > 0
}

void Widget.compareSensitiveFunction()
{
//! [16]
    x = QString.compare("aUtO", "AuTo", Qt.CaseInsensitive);  # x == 0
    y = QString.compare("auto", "Car", Qt.CaseSensitive);     # y > 0
    z = QString.compare("auto", "Car", Qt.CaseInsensitive);   # z < 0
//! [16]
}

void Widget.containsFunction()
{
//! [17]
    str = QString("Peter Pan")
    str.contains("peter", Qt.CaseInsensitive)    # returns true
//! [17]
}

void Widget.countFunction()
{
//! [18]
    str = QString("banana and panama")
    str.count(QRegExp("a[nm]a"))    # returns 4
//! [18]
}

void Widget.dataFunction()
{
//! [19]
//  Not Needed
    str = QString"Hello world"
    QChar *data = str.data()
    while (!data->isNull()) {
        qDebug() << data->unicode()
        ++data
    }
//! [19]
}

void Widget.endsWithFunction()
{
//! [20]
    str = QString("Bananas")
    str.endsWith("anas")         # returns true
    str.endsWith("pple")         # returns false
//! [20]
}

void Widget.fillFunction()
{
//! [21]
    str = QString("Berlin")
    str.fill('z')
    # str == "zzzzzz"

    str.fill('A', 2)
    # str == "AA"
//! [21]
}

void Widget.fromRawDataFunction()
{
//! [22]
     QRegExp pattern
     static const QChar unicode[] = {
             0x005A, 0x007F, 0x00A4, 0x0060,
             0x1009, 0x0020, 0x0020}
     int size = sizeof(unicode) / sizeof(QChar)

     QString str = QString.fromRawData(unicode, size)
     if (str.contains(QRegExp(pattern))) {
         # ...
//! [22] //! [23]
     }
//! [23]
}

void Widget.indexOfFunction()
{
//! [24]
    QString x = "sticky question"
    QString y = "sti"
    x.indexOf(y);               # returns 0
    x.indexOf(y, 1);            # returns 10
    x.indexOf(y, 10);           # returns 10
    x.indexOf(y, 11);           # returns -1
//! [24]
}

void Widget.firstIndexOfFunction()
{
//! [25]
    str = QString("the minimum")
    str.indexOf(QRegExp("m[aeiou]"), 0)       # returns 4
//! [25]
}

void Widget.insertFunction()
{
//! [26]
    str = QString("Meal")
    str.insert(1, QString("ontr"))
    # str == "Montreal"
//! [26]
}

void Widget.isEmptyFunction()
{
//! [27]
    QString().isEmpty()            # returns true
    QString("").isEmpty()          # returns true
    QString("x").isEmpty()         # returns false
    QString("abc").isEmpty()       # returns false
//! [27]
}

void Widget.isNullFunction()
{
//! [28]
    QString().isNull()             # returns true
    QString("").isNull()           # returns false
    QString("abc").isNull()        # returns false
//! [28]
}

void Widget.lastIndexOfFunction()
{
//! [29]
    QString x = "crazy azimuths"
    QString y = "az"
    x.lastIndexOf(y);           # returns 6
    x.lastIndexOf(y, 6);        # returns 6
    x.lastIndexOf(y, 5);        # returns 2
    x.lastIndexOf(y, 1);        # returns -1
//! [29]

//! [30]
    str = QString("the minimum")
    str.lastIndexOf(QRegExp("m[aeiou]"))      # returns 8
//! [30]
}

void Widget.leftFunction()
{
//! [31]
    x = QString("Pineapple")
    y = QString(x.left(4))      # y == "Pine"
//! [31]
}

void Widget.leftJustifiedFunction()
{
//! [32]
    s = QString("apple")
    t = QString(s.leftJustified(8, '.'))    # t == "apple..."
//! [32]

//! [33]
    str = QString("Pineapple")
    str = str.leftJustified(5, '.', True)    # str == "Pinea"
//! [33]
}

void Widget.midFunction()
{
//! [34]
    x = QString("Nine pineapples")
    y = QString(x.mid(5, 4))            # y == "pine"
    z = QString(x.mid(5))               # z == "pineapples"
//! [34]
}

void Widget.numberFunction()
{
//! [35]
    a = 63
    s = QString.number(a, 16)             # s == "3f"
    t = QString.number(a, 16).toUpper()     # t == "3F"
//! [35]
}

void Widget.prependFunction()
{
//! [36]
    x = QString("ship")
    y = QString("air")
    x.prepend(y)
    # x == "airship"
//! [36]
}

void Widget.removeFunction()
{
//! [37]
    s = QString("Montreal")
    s.remove(1, 4)
    # s == "Meal"
//! [37]

//! [38]
    QString t = "Ali Baba"
    t.remove(QChar('a'), Qt.CaseInsensitive)
    # t == "li Bb"
//! [38]

//! [39]
    r = QString("Telephone")
    r.remove(QRegExp("[aeiou]."))
    # r == "The"
//! [39]
}

void Widget.replaceFunction()
{
//! [40]
    x = QString("Say yes!")
    y = QString("no")
    x.replace(4, 3, y)
    # x == "Say no!"
//! [40]

//! [41]
    QString str = "colour behaviour flavour neighbour"
    str.replace(QString("ou"), QString("o"))
    # str == "color behavior flavor neighbor"
//! [41]

//! [42]
    s = QString("Banana")
    s.replace(QRegExp("a[mn]"), "ox")
    # s == "Boxoxa"
//! [42]

//! [43]
    t = QString("A <i>bon mot</i>.")
    t.replace(QRegExp("<i>([^<]*)</i>"), "\\emph{\\1}")
    # t == "A \\emph{bon mot}."
//! [43]

//! [86]
    QString equis = "xxxxxx"
    equis.replace("xx", "x")
    # equis == "xxx"    
//! [86]
}

void Widget.reserveFunction()
{
//! [44]
    result = QString()
    maxSize = 44

    result.reserve(maxSize)
    while condition:
        result.append(nextChar)

    result.squeeze()
//! [44]
}

void Widget.resizeFunction()
{
//! [45]
    s = QString("Hello world")
    s.resize(5)
    # s == "Hello"

    s.resize(8)
    # s == "Hello???" (where ? stands for any character)
//! [45]

//! [46]
    t = QString("Hello")
    t += QString(10, 'X')
    # t == "HelloXXXXXXXXXX"
//! [46]

//! [47]
    r = QString("Hello")
    r = r.leftJustified(10, ' ')
    # r == "Hello     "
//! [47]
}

void Widget.rightFunction()
{
//! [48]
    x = QString("Pineapple")
    y = x.right(5)      # y == "apple"
//! [48]
}

void Widget.rightJustifiedFunction()
{
//! [49]
    s = QString("apple")
    t = s.rightJustified(8, '.')    # t == "...apple"
//! [49]

//! [50]
    str = QString("Pineapple")
    str = str.rightJustified(5, '.', True)    # str == "Pinea"
//! [50]
}

void Widget.sectionFunction()
{ // NOT NEEDED
//! [51] //! [52]
    QString str
//! [51]
    QString csv = "forename,middlename,surname,phone"
    QString path = "/usr/local/bin/myapp"; # First field is empty
    QString.SectionFlag flag = QString.SectionSkipEmpty


    str = csv.section(',', 2, 2);   # str == "surname"
    str = path.section('/', 3, 4);  # str == "bin/myapp"
    str = path.section('/', 3, 3, flag); # str == "myapp"
//! [52]

//! [53]
    str = csv.section(',', -3, -2);  # str == "middlename,surname"
    str = path.section('/', -1); # str == "myapp"
//! [53]

//! [54]
    QString data = "forename**middlename**surname**phone"

    str = data.section("**", 2, 2); # str == "surname"
    str = data.section("**", -3, -2); # str == "middlename**surname"
//! [54]

//! [55]
    QString line = "forename\tmiddlename  surname \t \t phone"
    QRegExp sep("\\s+")
    str = line.section(sep, 2, 2); # s == "surname"
    str = line.section(sep, -3, -2); # s == "middlename  surname"
//! [55]
}

void Widget.setNumFunction()
{
//! [56]
    str = QString()
    str.setNum(1234)       # str == "1234"
//! [56]
}

void Widget.simplifiedFunction()
{
//! [57]
    str = QString("  lots\t of\nwhitespace\r\n ")
    str = str.simplified()
    # str == "lots of whitespace"
//! [57]
}

void Widget.sizeFunction()
{
//! [58]
    str = QString("World")
    n = str.size()         # n == 5
//! [58]
}

void Widget.splitFunction()
{
//! [59]
    str = QString("Some  text\n\twith  strange whitespace.")
    list = str.split(QRegExp("\\s+")) # A QStringList
    # list: [ "Some", "text", "with", "strange", "whitespace." ]
//! [59]

//! [60]
    str = QString("This time, a normal English sentence.")
    list = str.split(QRegExp("\\W+"), QString.SkipEmptyParts)
    # list: [ "This", "time", "a", "normal", "English", "sentence" ]
//! [60]

//! [61]
    str = QString("Now: this sentence fragment.")
    list = str.split(QRegExp("\\b"))
    # list: [ "", "Now", ": ", "this", " ", "sentence", " ", "fragment", "." ]
//! [61]
}

void Widget.splitCaseSensitiveFunction()
{
//! [62]
    str = QString("a,,b,c")

    list1 = str.split(",")
    # list1: [ "a", "", "b", "c" ]

    list2 = str.split(",", QString.SkipEmptyParts)
    # list2: [ "a", "b", "c" ]
//! [62]
}

void Widget.sprintfFunction()
{
//! [63]
    size_t BufSize
    char buf[BufSize]

    .snprintf(buf, BufSize, "%lld", 123456789LL)
    QString str = QString.fromAscii(buf)
//! [63]

//! [64]
    QString result
    QTextStream(&result) << "pi = " << 3.14
    # result == "pi = 3.14"
//! [64]
}

void Widget.startsWithFunction()
{
//! [65]
    QString str = "Bananas"
    str.startsWith("Ban")     # returns true
    str.startsWith("Car")     # returns false
//! [65]
}

void Widget.toDoubleFunction()
{
//! [66]
    str = QString("1234.56")
    val = str.toDouble()[0]   # val == 1234.56
//! [66]

//! [67]
    d, ok = QString( "1234.56e-02" ).toDouble() # ok == true, d == 12.3456
//! [67]

//! [68] //! [69]
    QLocale.setDefault(QLocale.C)
    d, ok = QString( "1234,56" ).toDouble() # ok == false
//! [68]
    d, ok = QString( "1234.56" ).toDouble() # ok == true, d == 1234.56

//! [69] //! [70]
    QLocale.setDefault(QLocale.German)
    d, ok = QString( "1234,56" ).toDouble() # ok == true, d == 1234.56
    d, ok = QString( "1234.56" ).toDouble() # ok == true, d == 1234.56

//! [70]
    QLocale.setDefault(QLocale.C)
    d, ok = QString( "1,234,567.89" ).toDouble() # ok == false
}

void Widget.toFloatFunction()
{
//! [71]
    str1 = QString("1234.56")
    str1.toFloat()             # returns (1234.56, True)

    str2 = QString("R2D2")
    str2.toFloat()          # returns (0.0, False)
//! [71]
}

void Widget.toIntFunction()
{
//! [72]
    str = QString("FF")
    hex, ok = str.toInt(16)       # hex == 255, ok == true
    dec, ok = str.toInt(10)       # dec == 0, ok == false
//! [72]
}

void Widget.toLongFunction()
{
//! [73]
    str = QString("FF")

    hex, ok = str.toLong(16)     # hex == 255, ok == true
    dec, ok = str.toLong(10)     # dec == 0, ok == false
//! [73]
}

void Widget.toLongLongFunction()
{
//! [74]
    str = QString("FF")

    hex, ok = str.toLongLong(16)      # hex == 255, ok == true
    dec, ok = str.toLongLong(10)      # dec == 0, ok == false
//! [74]
}

void Widget.toLowerFunction()
{
//! [75]
    str = QString("TROlltECH")
    str = str.toLower()        # str == "trolltech"
//! [75]
}

void Widget.toShortFunction()
{
//! [76]
    str = QString("FF")

    hex, ok = str.toShort(16)   # hex == 255, ok == true
    dec, ok = str.toShort(10)   # dec == 0, ok == false
//! [76]
}

void Widget.toUIntFunction()
{
//! [77]
    str = QString("FF")

    hex, ok = str.toUInt(16)     # hex == 255, ok == true
    dec, ok = str.toUInt(10)     # dec == 0, ok == false
//! [77]
}

void Widget.toULongFunction()
{
//! [78]
    str = QString("FF")

    hex, ok = str.toULong(16)   # hex == 255, ok == true
    dec, ok = str.toULong(10)   # dec == 0, ok == false
//! [78]
}

void Widget.toULongLongFunction()
{
//! [79]
    QString str = "FF"

    hex, ok = str.toULongLong(16)    # hex == 255, ok == true
    dec, ok = str.toULongLong(10)    # dec == 0, ok == false
//! [79]
}

void Widget.toUShortFunction()
{
//! [80]
    str = QString("FF")

    hex, ok = str.toUShort(16)     # hex == 255, ok == true
    dec, ok = str.toUShort(10)     # dec == 0, ok == false
//! [80]
}

void Widget.toUpperFunction()
{
//! [81]
    str = QString("TeXt")
    str = str.toUpper()        # str == "TEXT"
//! [81]
}

void Widget.trimmedFunction()
{
//! [82]
    str = QString("  lots\t of\nwhitespace\r\n ")
    str = str.trimmed()
    # str == "lots\t of\nwhitespace"
//! [82]
}

void Widget.truncateFunction()
{
//! [83]
    str = QString("Vladivostok")
    str.truncate(4)
    # str == "Vlad"
//! [83]
}

void Widget.plusEqualOperator()
{
//! [84]
    x = QString("free")
    y = QString("dom")
    x += y
    # x == "freedom"
//! [84]
}

void Widget.arrayOperator()
{
//! [85]
    str = QString(...)

    if (str[0] == QChar('?'))
        str[0] = QChar('_')
//! [85]
}

void Widget.midRefFunction()
{
//! [midRef]
    x = QString("Nine pineapples")
    y = x.midRef(5, 4)      # y == "pine"
    z = x.midRef(5)         # z == "pineapples"
//! [midRef]
}

void Widget.leftRefFunction()
{
//! [leftRef]
    x = QString("Pineapple")
    y = x.leftRef(4)       # y == "Pine"
//! [leftRef]
}

void Widget.rightRefFunction()
{
//! [rightRef]
    x = QString("Pineapple")
    y = x.rightRef(5)       # y == "apple"
//! [rightRef]
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv)
    Widget widget
    widget.show()
    return app.exec()
}
