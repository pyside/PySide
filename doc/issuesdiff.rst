PySide issues and specificities
*******************************

This document shows some points not supported yet by Boost.python
and PySide.

Deprecated Methods
------------------

The deprecated methods before Qt 4.4 is not supported by PySide,
e.g.: `QColor.dark()` and `QColor.light()`.

**How to solve:** update the methods with new ones like `QColor.darker()`
and `QColor.lighter()`.

Class methods with static and normal methods with the same signature
--------------------------------------------------------------------

Boost.Python does not support static methods and member methods
with the same signature. The static versions is renamed to
*classMethodName*.

**Example:** QFile.permissions() and QFile.permissions(QString)

**How to solve:** for static methods use QFile.filePermissions(QString)

