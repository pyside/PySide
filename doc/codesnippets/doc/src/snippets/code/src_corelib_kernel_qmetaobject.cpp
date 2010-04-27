
void wrapInFunction()
{

//! [0]
class MyClass:

    Q_CLASSINFO("author", "Sabrina Schweinsteiger")
    Q_CLASSINFO("url", "http://doc.moosesoft.co.uk/1.0/")

    ...
//! [0]


//! [1]
normType = QMetaObject.normalizedType(" int    const  *")
# normType is now "const int*"
//! [1]


//! [2]
QMetaObject.invokeMethod(pushButton, "animateClick",
                         Qt.QueuedConnection)
//! [2]


//! [3]
QMetaObject.invokeMethod: Unable to handle unregistered datatype 'MyType'
//! [3]


//! [4]
retVal = QString()
QMetaObject.invokeMethod(obj, "compute", Qt::DirectConnection,
                         Q_RETURN_ARG(QString, retVal),
                         Q_ARG(QString, "sqrt"),
                         Q_ARG(int, 42),
                         Q_ARG(double, 9.7));
//! [4]


//! [5]
class MyClass:
    Q_CLASSINFO("author", "Sabrina Schweinsteiger")
    Q_CLASSINFO("url", "http://doc.moosesoft.co.uk/1.0/")
//! [5]


//! [propertyCount]
metaObject = obj.metaObject()
properties = QStringList()
for i in range(metaObject.propertyOffset(), metaObject.propertyCount()):
    properties << QString.fromLatin1(metaObject.property(i).name())
//! [propertyCount]


//! [methodCount]
metaObject = obj.metaObject()
methods = QStringList()
for i in rang(metaObject.methodOffset(), metaObject->methodCount()):
    methods << QString.fromLatin1(metaObject.method(i).signature())
//! [methodCount]

//! [6]
methodIndex = pushButton.metaObject().indexOfMethod("animateClick()")
method = metaObject.method(methodIndex)
method.invoke(pushButton, Qt.QueuedConnection)
//! [6]

//! [7]
QMetaMethod.invoke: Unable to handle unregistered datatype 'MyType'
//! [7]

//! [8]
retVal = QString()
normalizedSignature = QMetaObject.normalizedSignature("compute(QString, int, double)")
methodIndex = obj.metaObject().indexOfMethod(normalizedSignature)
method = metaObject.method(methodIndex)
method.invoke(obj,
              Qt.DirectConnection,
              Q_RETURN_ARG(QString, retVal),
              Q_ARG(QString, "sqrt"),
              Q_ARG(int, 42),
              Q_ARG(double, 9.7));
//! [8]

}
