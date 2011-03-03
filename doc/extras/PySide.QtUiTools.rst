These forms are processed at run-time to produce dynamically-generated user interfaces. In order to generate a form at run-time, a resource file containing a UI file is needed.

A form loader object, provided by the QUiLoader class, is used to construct the user interface. This user interface can be retrieved from any QIODevice; for example, a QFile object can be used to obtain a form stored in a project's resources. The :meth:`PySide.QtUiTools.QUiLoader.load` function takes the user interface description contained in the file and constructs the form widget.

To include the definitions of the module's classes, use the following directive:

::

    import PySide..QtUiTools
