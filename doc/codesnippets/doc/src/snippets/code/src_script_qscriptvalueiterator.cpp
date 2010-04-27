//! [0]
object = QScriptValue()
...
it = QScriptValueIterator(object)
while it.hasNext():
    it.next()
    print "%s:%s" % (it.name(), it.value().toString())
//! [0]


//! [1]
QScriptValue obj = ... // the object to iterate over
while obj.isObject():
    it = QScriptValueIterator(obj)
    while it.hasNext():
        it.next()
        print it.name()
    obj = obj.prototype()
//! [1]


//! [2]
while it.hasNext():
    it.next()
    if it.flags() & QScriptValue::SkipInEnumeration:
        continue
    print "found enumerated property: %s" % it.name()
//! [2]
