.. module:: PySide.QtDeclarative
.. _ListProperty:

ListProperty
************

Synopsis
--------

    The The :class:`~.ListProperty` class allows applications to expose list-like properties to QML.

Detailed Description
--------------------

    The :class:`~.ListProperty` class provides a replacement to QDeclarativeListProperty.

    :class:`~.ListProperty` is a subclass of :class:`QtCore.Property`, that support the following keywords.

    `type`      the type used in the list
    `append`    Function used to append itens
    `at`        Function used to retrieve item from the list
    `clear`     Function used to clear the list
    `count`     Function used to retrieve the list size


    QML has many list properties, where more than one object value can be assigned. The use of a list property from QML looks like this:

    ::
        FruitBasket {
             fruit: [
                 Apple {},
                 Orange{},
                 Banana{}
             ]
        }

    The :class:`~.ListProperty` encapsulates a group of callbacks that represent the set of actions QML can perform on the list - adding items, retrieving items and clearing the list. In the future, additional operations may be supported. All list properties must implement the append operation, but the rest are optional.
    To provide a list property, a class must implement the operation callbacks, and then return an appropriate value from the property getter. List properties should have no setter. In the example above, the  ListProperty declarative will look like this:

    ::
        slices = ListProperty(PieSlice, append=appendSlice)


    Note: :class:`~.ListProperty` can only be used for lists of QObject-derived object pointers.


