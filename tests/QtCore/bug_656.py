from PySide.QtCore import *

class CoreApp(QCoreApplication):
    def __init__(self,*args):
        super(CoreApp,self).__init__(*args)
        # It shouldn't crash after the __init__ call

import sys
app = CoreApp(sys.argv)
