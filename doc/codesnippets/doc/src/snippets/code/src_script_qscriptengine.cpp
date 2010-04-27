//! [0]
myEngine = QScriptEngine()
three = myEngine.evaluate("1 + 2")
//! [0]


//! [1]
fun = myEngine.evaluate("function(a, b) { return a + b }");
args = QScriptValueList()
args << 1 << 2
threeAgain = fun.call(QScriptValue(), args)
//! [1]


//! [2]
fileName = "helloworld.qs"
scriptFile = QFile(fileName)
if !scriptFile.open(QIODevice.ReadOnly):
    # handle error
stream = QTextStream(scriptFile)
contents = stream.readAll()
scriptFile.close()
myEngine.evaluate(contents, fileName)
//! [2]


//! [3]
myEngine.globalObject().setProperty("myNumber", 123)
...
myNumberPlusOne = myEngine.evaluate("myNumber + 1")
//! [3]


//! [4]
result = myEngine.evaluate(...)
if myEngine.hasUncaughtException():
    line = myEngine.uncaughtExceptionLineNumber()
    print "uncaught exception at line", line, ":", result.toString()
//! [4]


//! [5]
button = QPushButton()
QScriptValue scriptButton = myEngine.QObject(button)
myEngine.globalObject().setProperty("button", scriptButton)

myEngine.evaluate("button.checkable = True")

print scriptButton.property("checkable").toBoolean()
scriptButton.property("show").call() # call the show() slot
//! [5]


//! [6]
def myAdd(context, engine):
   a = context.argument(0)
   b = context.argument(1)
   return a.toNumber() + b.toNumber()
//! [6]


//! [7]
fun = myEngine.Function(myAdd)
myEngine.globalObject().setProperty("myAdd", fun)
//! [7]


//! [8]
result = myEngine.evaluate("myAdd(myNumber, 1)")
//! [8]


//! [9]
def Foo(context, engine):
    if context.calledAsConstructor():
        # initialize the  object
        context.selfObject().setProperty("bar", ...)
        # ...
        # return a non-object value to indicate that the
        # selfObject() should be the result of the " Foo()" expression
        return engine.undefinedValue()
    else:
        # not called as " Foo()", just "Foo()"
        # create our own object and return that one
        object = engine.Object()
        object.setPrototype(context.callee().property("prototype"))
        object.setProperty("baz", ...)
        return object
...

fooProto = engine.Object()
fooProto.setProperty("whatever", ...)
engine.globalObject().setProperty("Foo", engine->Function(Foo, fooProto))
//! [9]


//! [10]
class Bar:
     ... 

def constructBar(context, engine):
    bar = Bar()
    # initialize from arguments in context, if desired
    ...
    return engine.toScriptValue(bar)

class BarPrototype(QObject, QScriptable):
# provide the scriptable interface of self type using slots and properties
...

...

# create and register the Bar prototype and constructor in the engine
barPrototypeObject =  BarPrototype(...)
barProto = engine.QObject(barPrototypeObject)
engine.setDefaultPrototype(qMetaTypeId(Bar), barProto)
barCtor = engine.Function(constructBar, barProto)
engine.globalObject().setProperty("Bar", barCtor)
//! [10]


//! [11]
def getSetFoo(context,engine):
    callee = context.callee()
    if context.argumentCount() == 1: # writing?
        callee.setProperty("value", context.argument(0))
    return callee.property("value")
}

....

object = engine.Object()
object.setProperty("foo", engine.Function(getSetFoo),
    QScriptValue.PropertyGetter | QScriptValue::PropertySetter)
//! [11]


//! [12]
object = engine.Object()
object.setProperty("foo", engine.Function(getFoo), QScriptValue.PropertyGetter)
object.setProperty("foo", engine.Function(setFoo), QScriptValue.PropertySetter)
//! [12]


//! [13]
Q_SCRIPT_DECLARE_QMETAOBJECT(QLineEdit, QWidget*)

...

lineEditClass = engine.scriptValueFromQMetaObject(QLineEdit)
engine.globalObject().setProperty("QLineEdit", lineEditClass)
//! [13]


//! [14]
if hello && world:
    print("hello world")
//! [14]


//! [15]
if hello &&
//! [15]


//! [16]
0 = 0
//! [16]


//! [17]
./test.js
//! [17]


//! [18]
foo["bar"]
//! [18]


//! [19]
engine = QScriptEngine()
context = engine.pushContext()
context.activationObject().setProperty("myArg", 123)
engine.evaluate("var tmp = myArg + 42")
...
engine.popContext()
//! [19]


//! [20]
class MyStruct:
    x = 0
    y = 0
//! [20]


//! [21]
Q_DECLARE_METATYPE(MyStruct)
//! [21]


//! [22]
def toScriptValue(engine, s):
  obj = engine.Object()
  obj.setProperty("x", s.x)
  obj.setProperty("y", s.y)
  return obj

def fromScriptValue(obj, s):
  s.x = obj.property("x").toInt32()
  s.y = obj.property("y").toInt32()
//! [22]


//! [23]
qScriptRegisterMetaType(engine, toScriptValue, fromScriptValue)
//! [23]


//! [24]
s = context.argument(0)
...
s2 = MyStruct()
s2.x = s.x + 10
s2.y = s.y + 20
v = engine.toScriptValue(s2)
//! [24]


//! [25]
def createMyStruct(cx, engine):
    s = MyStruct()
    s.x = 123
    s.y = 456
    return engine.toScriptValue(s)
...

ctor = engine.Function(createMyStruct)
engine.globalObject().setProperty("MyStruct", ctor)
//! [25]


//! [26]
Q_DECLARE_METATYPE(QVector<int>)

...

qScriptRegisterSequenceMetaType<QVector<int> >(engine)
...
v = engine.evaluate("[5, 1, 3, 2]")
v.sort()
a = engine.toScriptValue(v)
print a.toString() # outputs "[1, 2, 3, 5]"
//! [26]

//! [27]
def mySpecialQObjectConstructor(context, engine):
    parent = context.argument(0).toQObject()
    object =  QObject(parent)
    return engine.QObject(object, QScriptEngine.ScriptOwnership)

...

ctor = engine.Function(mySpecialQObjectConstructor)
metaObject = engine.QMetaObject(QObject.staticMetaObject, ctor)
engine.globalObject().setProperty("QObject", metaObject)

result = engine.evaluate(" QObject()")
//! [27]
