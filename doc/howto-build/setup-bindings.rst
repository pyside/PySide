***************
Qt 4.6 Bindings
***************

Overview
========

These bindings allow access of Qt 4.6 libraries as Python modules,
making them available just using the ``import`` command.

The build process is comprised of two stages: in a first moment the
bindings source code are created from the Qt 4.6 headers by calling
the :ref:`boost-python-generator` with apropriate parameters; the
generated files are then compiled and linked together to form the
bindings libraries.

The bindings available at the moment are listed below:

   + QtCore
   + QtGui
   + QtHelp
   + QtMultimedia
   + QtNetwork
   + QtOpenGL
   + QtScript
   + QtScriptTools
   + QtSql
   + QtSvg
   + QtUiTools
   + QtWebKit
   + QtXml
   + QtXmlPatterns

Getting the sources
===================

* Download URL: http://www.pyside.org/downloads/

Build requirements
==================

   + CMake (>= 2.6.0)
   + Qt 4.6 libraries + headers
   + Boost.Python + headers (>= 1.40.0)
   + :ref:`boost-python-generator`


Building and installing
=======================

To build and install just follow the generic cmake instructions in
section :ref:`cmake-primer`.

Be advised that the build process can be rather lenghty because of the
number of source files that will be compiled.

Debian packaging
================

.. note:: For the time being the Debian packaging uses Qt 4.5 as dependency, therefore the generated bindings will be for this version of Qt.

In order to compile this package in a debian environment, make sure the
following packages are installed:

* debhelper (>= 5)
* cdbs
* cmake (>= 2.6.0)
* python-all-dev
* python-central (>= 0.6)
* boostpythongenerator (>= 0.3)
* libboost-python1.40-dev (>= 1.40.0)
* libqt4-dev (>= 4.5)

And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
