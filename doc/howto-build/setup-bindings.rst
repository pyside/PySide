***************
Qt 4.6 Bindings
***************

Overview
========

These bindings allow access of Qt 4.6 libraries as Python modules,
making them available just using the ``import`` command.

The build process is comprised of two stages: in a first moment the
bindings source code are created from the Qt 4.6 headers by calling
the :ref:`generator-runner` with apropriate parameters; the
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
   + Phonon

Getting the sources
===================

* Download URL: http://www.pyside.org/downloads/

Build requirements
==================

   + CMake (>= 2.6.0)
   + Qt4.6 libraries and development headers
   + Python dev libraries
   + Shiboken libraries
   + :ref:`generator-runner`


Building and installing
=======================

To build and install just follow the generic cmake instructions in
section :ref:`cmake-primer`.

Be advised that the build process can be rather lenghty because of the
number of source files that will be compiled.

Debian packaging
================

.. note:: Qt 4.6 is available for Debian in the testing branch (squeeze), Ubuntu 10.04 (Lucid Lynx), and in Maemo 5 (Fremantle) in the upcoming PR 1.2 update. 

In order to compile this package in a Debian environment, make sure the
following packages are installed:

* debhelper (>= 7)
* cmake (>= 2.6.0)
* python-all-dev
* python-all-dbg
* python-support (>= 0.3.9)
* libqt4-dev
* libphonon-dev
* libqt4-opengl-dev
* shiboken (>= 0.2)
* generatorrunner (>= 0.4)
* libshiboken-dev (>= 0.2.0)


And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
