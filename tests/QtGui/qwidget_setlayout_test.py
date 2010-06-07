#!/usr/bin/python

import unittest

from PySide.QtGui import QWidget, QVBoxLayout, QPushButton, QApplication, QHBoxLayout
from helper import UsesQApplication

class QWidgetTest(UsesQApplication):

    def test_setLayout(self):
        layout = QVBoxLayout()
        btn1 = QPushButton("button_v1")
        layout.addWidget(btn1)

        btn2 = QPushButton("button_v2")
        layout.addWidget(btn2)

        layout2 = QHBoxLayout()

        btn1 = QPushButton("button_h1")
        layout2.addWidget(btn1)

        btn2 = QPushButton("button_h2")
        layout2.addWidget(btn2)

        layout.addLayout(layout2)

        widget = QWidget()
        widget.setLayout(layout)

if __name__ == '__main__':
    unittest.main()

