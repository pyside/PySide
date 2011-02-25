
.. _pysideapi2:

PySide API 2
************

Since the beginning one of the PySide goals was to be API compatible with PyQt4,
but with some (documented) exceptions. For example, PySide will not export to
Python components marked as deprecated on C++ Qt. All the modifications follow
the `PSEP101 <http://www.pyside.org/docs/pseps/psep-0101.html>`_ as its guideline.

The release 4.7 of PyQt4 came with improvements on the pythonic front, being
the extinction of QString a good example. PySide followed this change, except in
one point: while PyQt4 has conserved the old behavior as optional, PySide
bindings fully adopted the new API - completely removing QString. No turning
back. Thus remember to update your source code to the new API, this will ensure
your code will run on both bindings.


__hash__() function return value
================================

The hash value returned for the classes :class:`PySide.QtCore.QDate`, :class:`PySide.QtCore.QDateTime`, :class:`PySide.QtCore.QTime`, :class:`PySide.QtCore.QUrl` will be
based on their string representations, thus objects with the same value will
produce the same hash.


QString
=======

Methods that change QString arguments
-------------------------------------

Methods and functions that change the contents of a QString argument were
modified to receive an immutable Python unicode (or str) and return another
Python unicode/str as the modified string.

The following methods had their return types modified this way:

**Classes:** QAbstractSpinBox, QDateTimeEdit, QDoubleSpinBox, QSpinBox, QValidator

- *fixup(string)*: string
- *validate(string, int)*: [QValidator.State, string, int]


**Classes:** QDoubleValidator, QIntValidator, QRegExpValidator

- *validate(string, int)*: [QValidator.State, string, int]

**Class:** QClipboard

- *text(string, QClipboard.Mode mode=QClipboard.Clipboard)*: [string, string]


**Class:** QFileDialog

Instead of *getOpenFileNameAndFilter()*, *getOpenFileNamesAndFilter()* and *getSaveFileNameAndFilter()* like PyQt4 does,
PySide has modified the original methods to return a tuple.

- *getOpenFileName(QWidget parent=None, str caption=None, str dir=None, str filter=None, QFileDialog.Options options=0)*: [string, filter]
- *getOpenFileNames(QWidget parent=None, str caption=None, str dir=None, str filter=None, QFileDialog.Options options=0)*: [list(string), filter]
- *getSaveFileName(QWidget parent=None, str caption=None, str dir=None, str filter=None, QFileDialog.Options options=0)*: [string, filter]

**Class:** QWebPage

- *javaScriptPrompt(QWebFrame, string, string)*: [bool, string]

Other QString related changes
-----------------------------

**Classes:** QFontMetrics and QFontMetricsF

They had two new methods added. Both take a string of one character and convert to a QChar (to call the C++ counterpart):

- widthChar(string)
- boundingRectChar(string)


QTextStream
===========

Inside this class some renames were applied to avoid clashes with native Python functions. They are: *bin_()*, *hex_()* and *oct_()*.
The only modification was the addition of '_' character.


QVariant
========

As QVariant was removed, any function expecting it can receive any Python object (None is an invalid QVariant). The same rule is valid when returning something: the returned QVariant will be converted to the its original Python object type.

When a method expects a *QVariant::Type* the programmer can use a string (the type name) or the type itself.
