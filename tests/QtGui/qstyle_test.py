
import unittest
from helper import UsesQApplication

from PySide.QtGui import QWidget, QLabel, QFontComboBox, QStyleFactory

class SetStyleTest(UsesQApplication):
    '''Tests setting the same QStyle for all objects in a UI hierarchy.'''

    def testSetStyle(self):
        '''All this test have to do is not break with some invalid Python wrapper.'''

        def setStyleHelper(widget, style):
            widget.setStyle(style)
            widget.setPalette(style.standardPalette())
            for child in widget.children():
                if isinstance(child, QWidget):
                    setStyleHelper(child, style)

        container = QWidget()
        # QFontComboBox is used because it has an QLineEdit created in C++ inside it,
        # and if the QWidget.setStyle(style) steals the ownership of the style
        # for the C++ originated widget everything will break.
        fontComboBox = QFontComboBox(container)
        label = QLabel(container)
        label.setText('Label')
        style = QStyleFactory.create(QStyleFactory.keys()[0])
        setStyleHelper(container, style)

if __name__ == '__main__':
    unittest.main()

