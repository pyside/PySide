
.. _generator-runner:

****************
Generator Runner
****************

Overview
=========================================

The **Generator Runner** (A.K.A. :program:`generatorrunner`) is the
program that controls the bindings generation process according to the
rules given by the user through headers, typesystem files and generator
front-ends (such as :ref:`shiboken-generator`). It depends on
:ref:`api-extractor` library.


Getting the sources
===================

* Download URL: http://www.pyside.org/downloads/

Build requirements
==================

+ CMake >= 2.6.0
+ Qt4.5 libraries and development headers >= 4.5.0
+ :ref:`api-extractor` + development headers

Building and installing
=======================

To build and install just follow the generic CMake instructions in
section :ref:`cmake-primer`.

Debian packaging
================

In order to compile this package in a Debian environment, make sure the
following packages are installed:

* debhelper (>= 5)
* cdbs
* cmake (>= 2.6.0)
* libqt4-dev (>= 4.5)
* libapiextractor-dev (>= 0.3.2)

And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
