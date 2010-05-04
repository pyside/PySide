How to generate this documentation
**********************************

Pre-requisites
--------------

You will need:

1. Qt4 source code (for API documentation).
2. Generator runner with shiboken plugin
3. PySide source code
4. cmake
5. sphinx
6. graphviz

Extracting documentation from Qt4
---------------------------------

The API documentation is generated from source code comments (for now, just
``qdoc3`` tool is supported, ``doxygen`` support will be added soon).

``qdoc3`` is the tool used to generate the oficial Qt4 documentation, you will
use it to generate a bunch of XML files that will be used by the generator
to create the documentation.

You need to tell PySide where it can find the Qt source code, to do this, when running cmake add the following parameters:

::

    $ mkdir build
    $ cmake -DQT_SRC_DIR=PATH_TO_QT_SOURCE_DIR ..
    $ make apidoc
    $ make apidocinstall

Where:
    * *PATH_TO_QT_SOURCE_DIR* is the path to the Qt sources.

The documentation will be installed at ``<INSTALL_PREFIX>/share/doc/pyside/index.html``, change
the *CMAKE_INSTALL_PREFIX* value if you want to install the documentation in another
directory.

If you want to have inheritance graphs on the generated documentation, make sure you have the bindings installed before generate the documentation.
