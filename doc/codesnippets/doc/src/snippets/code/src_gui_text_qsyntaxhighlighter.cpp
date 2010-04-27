//! [0]
editor = QTextEdit()
highlighter = MyHighlighter(editor.document())
//! [0]


//! [1]
class MyHighlighter(QSyntaxHighlighter):
    def highlightBlock(self, text):
        myClassFormat = QTextCharFormat()
        myClassFormat.setFontWeight(QFont.Bold)
        myClassFormat.setForeground(Qt.darkMagenta)
        pattern = QString("\\bMy[A-Za-z]+\\b")

        expression = QRegExp(pattern)
        index = text.indexOf(expression)
        while index >= 0:
            length = expression.matchedLength()
            setFormat(index, length, myClassFormat)
            index = text.indexOf(expression, index + length)
//! [1]


//! [2]
multiLineCommentFormat = QTextCharFormat()
multiLineCommentFormat.setForeground(Qt.red)

startExpression = QRegExp("/\\*")
endExpression = QRegExp("\\*/")

setCurrentBlockState(0)

startIndex = 0
if previousBlockState() != 1:
    startIndex = text.indexOf(startExpression)

while startIndex >= 0:
    endIndex = text.indexOf(endExpression, startIndex)
    if endIndex == -1:
       setCurrentBlockState(1)
       commentLength = text.length() - startIndex
    else:
       commentLength = endIndex - startIndex
                       + endExpression.matchedLength()

    setFormat(startIndex, commentLength, multiLineCommentFormat)
    startIndex = text.indexOf(startExpression,
                              startIndex + commentLength)
//! [2]


//! [3]
class MyHighlighter(QSyntaxHighlighter):
    def highlightBlock(self, text):
        myClassFormat = QTextCharFormat()
        myClassFormat.setFontWeight(QFont.Bold)
        myClassFormat.setForeground(Qt.darkMagenta)
        pattern = QString("\\bMy[A-Za-z]+\\b")

        expression = QRegExp(pattern)
        index = text.indexOf(expression)
        while index >= 0:
            length = expression.matchedLength()
            setFormat(index, length, myClassFormat)
            index = text.indexOf(expression, index + length)
//! [3]


//! [4]
class BlockData(QTextBlockUserData):
    def __init__(self):
        # ...
        self.parentheses = []
//! [4]
