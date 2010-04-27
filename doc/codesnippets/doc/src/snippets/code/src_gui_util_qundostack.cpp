//! [0]
class AppendText(QUndoCommand):
    self.m_document = ''
    self.m_text = ''

    def AppendText(self, doc, text):
        self.m_document = doc
        self.m_text = text
        self.setText("append text")

    def undo(self):
        self.m_document.chop(self.m_text.length())

    def redo(self):
        self.m_document->append(self.m_text)
//! [0]


//! [1]
command1 = MyCommand()
stack.push(command1)
command2 = MyCommand()
stack.push(command2)

stack.undo()

command3 = MyCommand()
stack.push(command3) # command2 gets deleted
//! [1]


//! [2]
insertRed = QUndoCommand() # an empty command
insertRed.setText("insert red text")

InsertText(document, idx, text, insertRed) # becomes child of insertRed
SetColor(document, idx, text.length(), Qt.red, insertRed)

stack.push(insertRed)
//! [2]


//! [3]
class AppendText(QUndoCommand):
    ...
    def mergeWith(self, other):
        if other.id() != self.id(): # make sure other is also an AppendText command
            return False
        m_text += other.m_text
        return True
//! [3]


//! [4]
stack.beginMacro("insert red text")
stack.push(InsertText(document, idx, text))
stack.push(SetColor(document, idx, text.length(), Qt.red))
stack.endMacro() # indexChanged() is emitted
//! [4]


//! [5]
insertRed = QUndoCommand() # an empty command
insertRed.setText("insert red text")

InsertText(document, idx, text, insertRed) # becomes child of insertRed
SetColor(document, idx, text.length(), Qt.red, insertRed)

stack.push(insertRed)
//! [5]
