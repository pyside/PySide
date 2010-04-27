//! [0]
class MyScriptableObject(QObject, QScriptable):
...
    def doSomething(self):
        ...
    def doSomethingElse(self):
        ...
//! [0]


//! [1]

def doSomething(self):
    self.context().throwError('Threw an error from a slot')

def doSomethingElse(self):
    return self.thisObject()

//! [1]
