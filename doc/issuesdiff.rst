PySide issues and specificities
*******************************

This document shows some points not supported by PySide.

Deprecated Methods
------------------

The deprecated methods before Qt 4.4 is not supported by PySide,
e.g.: `QColor.dark()` and `QColor.light()`.

**How to solve:** update the methods with new ones like `QColor.darker()`
and `QColor.lighter()`.

