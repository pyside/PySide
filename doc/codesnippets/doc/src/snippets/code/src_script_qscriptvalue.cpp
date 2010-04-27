//! [0]
myEngine = QScriptEngine()
myObject = myEngine.newObject()
myOtherObject = myEngine.newObject()
myObject.setProperty("myChild", myOtherObject)
myObject.setProperty("name", "John Doe")
//! [0]


//! [1]
val = QScriptValue(myEngine, 123)
myObject.setProperty("myReadOnlyProperty", val, QScriptValue.ReadOnly)
//! [1]


//! [2]
engine = QScriptEngine()
engine.evaluate("function fullName() { return this.firstName + ' ' + this.lastName; }")
engine.evaluate("somePerson = { firstName: 'John', lastName: 'Doe' }")

global_ = engine.globalObject()
fullName = global_.property("fullName")
who = global_.property("somePerson")
print fullName.call(who).toString() # "John Doe"

engine.evaluate("function cube(x) { return x * x * x; }")
QScriptValue cube = global_.property("cube")
args = QScriptValueList()
args << 3
print cube.call(QScriptValue(), args).toNumber() # 27
//! [2]


//! [3]

def myNativeFunction(context, engine):
    otherFunction = ...

    return otherFunction.call(context.thisObject(), context.argumentsObject())

//! [3]
