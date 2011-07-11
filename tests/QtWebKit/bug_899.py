import unittest
from PySide.QtCore import Property, QObject
from PySide.QtWebKit import QWebView
from helper import TimedQApplication

class TestLambdaPropery(TimedQApplication):

    def testBug899(self):
        html = '''
        <html><body>
        <script type="text/javascript">
        document.write("<p>"+py_obj.list1+"</p>")
        document.write("<p>"+py_obj.list2+"</p>")
        </script>
        </body></html>
        '''

        class Obj(object):
            list1 = ['foo', 'bar', 'baz']
            list2 = ['fi', 'fo', 'fum']

        obj = Obj()

        wrapper_dict = {}
        for name in ('list1', 'list2'):
            getter = lambda arg=None, name=name: getattr(obj, name)
            wrapper_dict[name] = Property('QVariantList', getter)
        wrapper = type('PyObj', (QObject,), wrapper_dict)

        view = QWebView()
        view.page().mainFrame().addToJavaScriptWindowObject('py_obj', wrapper())
        view.setHtml(html)


if __name__ == '__main__':
    unittest.main()
