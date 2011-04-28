Getting PySide and Qt version
*****************************

PySide exports their version numbers among the version of Qt used to compile PySide in a pythonnic way, you can check it using the variables:

::

    import PySide

    # Prints PySide version
    # e.g. 1.0.2
    print PySide.__version__

    # Gets a tuple with each version component
    # e.g. (1, 0, 2, 'final', 1)
    print PySide.__version_info__

    # Prints the Qt version used to compile PySide
    # e.g. "4.7.2"
    print PySide.QtCore.__version__

    # Gets a tuple with each version components of Qt used to compile PySide
    # e.g. (4, 7, 2)
    print PySide.QtCore.__version_info__


Note that the Qt version used to compile PySide may differ from the version used to run PySide, to get the current running Qt version you can do:

::

    print PySide.QtCore.qVersion()
