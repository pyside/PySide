Use of QPropery in PySide
*************************

PySide implements the function 'QProperty' which allows to declare properties compatible with QMetaProperties.


Using PySide.QProperty()
------------------------

The QProperty works like Q_PROPERTY macro, and uses the same arguments.

QProperty(getFunction, [setFunction], [resetFunction], [Designable], [Scriptable], [Stored], [User])


The example below uses QProperty function to export a property in QMetaObject data.

::

    ...
    clas MyObject(QObject):
        def getX(self):
            ...

        def setX(self, value):
            ...

        def resetX(self):
            ...

        X = QProperty(getX, setX, resetX, True, True, True, True)

    ...


The exported property works like native python property on python side. See the example below.

::

    ...
    o = MyObject()
    o.X = 10
    print o.X
    ...

