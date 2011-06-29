import unittest
from PySide.QtCore import Property, QObject
from PySide.QtWebKit import QWebView
from helper import TimedQApplication

class TestLoadFinished(TimedQApplication):

    def setUp(self):
        TimedQApplication.setUp(self, timeout=1000)

    def tearDown(self):
        TimedQApplication.tearDown(self)

    def testQVariantListProperty(self):
        class Obj(object):
            list = ['foo', 'bar', 'baz']

        obj = Obj()

        wrapper_dict = {}
        for name in ['list']:
            getter = lambda arg=None, name=name: getattr(obj, name)
            wrapper_dict[name] = Property('QVariantList', getter)
        wrapper = type('PyObj', (QObject,), wrapper_dict)

        view = QWebView()
        frame = view.page().mainFrame()
        frame.addToJavaScriptWindowObject('py_obj', wrapper())

        html = '''
        <html><body>
        <script type="text/javascript">
        document.write(py_obj.list)
        </script>
        </body></html>
        '''
        view.setHtml(html)
        view.show()
        self.app.exec_()


if __name__ == '__main__':
    unittest.main()
