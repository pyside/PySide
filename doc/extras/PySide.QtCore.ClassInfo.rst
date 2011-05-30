.. module:: PySide.QtCore
.. _ClassInfo:

ClassInfo
*********

This class is used to associates extra information to the class, which is available
using QObject.metaObject(). Qt and PySide doesn't use this information.

The extra information takes the form of a dictionary with key and value in a literal string.

.. note:: This Class is a implementation of Q_CLASSINFO macro.
   

Example
-------

::

    @ClassInfo(Author='PySide Team', URL='http://www.pyside.org')
    class MyObject(QObject):
        ...

