
.. _shiboken-generator:

******************
Shiboken Generator
******************

Overview
=========================================

The **Shiboken Generator** (A.K.A. :program:`shiboken`) is
the plugin that creates the PySide bindings source files from Qt headers
and auxiliary files  (typesystems, ``global.h`` and glue files). It depends on
:ref:`generator-runner` and :ref:`api-extractor` library.


Getting the sources
===================

* Download URL: http://www.pyside.org/downloads/

Build requirements
==================

+ CMake >= 2.6.0
+ Qt libraries and development headers >= 4.5.0
+ :ref:`api-extractor` + development headers
+ :ref:`generator-runner` + development headers

Building and installing
=======================

To build and install just follow the generic cmake instructions in
section :ref:`cmake-primer`.

Debian packaging
================

In order to compile this package in a debian environment, make sure the
following packages are installed:

* debhelper (>= 5)
* cdbs
* cmake (>= 2.6.0)
* libqt4-dev (>= 4.5)
* libapiextractor-dev (>= 0.3.2)
* libgenrunner-dev (>= 0.3.2a1)

And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
