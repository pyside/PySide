
import os
import sys
import unittest

from PySide.QtCore import QUrl, QTimer
from PySide.QtGui import QApplication, QLabel
from PySide.QtWebKit import QWebPluginFactory, QWebView, QWebSettings

from helper import UsesQApplication

class PluginFactory(QWebPluginFactory):

    def plugins(self):
        plugins = []

        mime = self.MimeType()
        mime.name = 'DummyFile'
        mime.fileExtensions = ['.pys']

        plugin = self.Plugin()
        plugin.name = 'DummyPlugin'
        plugin.mimeTypes = [mime]

        plugins.append(plugin)

        return plugins

    def create(self, mimeType, url, argumentNames, argumentValues):
        if mimeType != 'application/x-dummy':
            return None

        for name, value in zip(argumentNames, argumentValues):
            if name == 'text':
                text = value
        else:
            text = "Webkit plugins!"

        widget = QLabel(text)
        return widget

class TestPlugin(UsesQApplication):

    def testPlugin(self):
        view = QWebView()
        fac = PluginFactory()
        view.page().setPluginFactory(fac)
        QWebSettings.globalSettings().setAttribute(QWebSettings.PluginsEnabled, True)

        view.load(QUrl(os.path.join(os.path.abspath(os.path.dirname(__file__)), 'qmlplugin', 'index.html')))

        view.resize(840, 600)
        view.show()

        QTimer.singleShot(500, self.app.quit)

        self.app.exec_()


if __name__ == '__main__':
    unittest.main()
