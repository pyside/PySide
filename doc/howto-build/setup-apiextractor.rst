
.. _api-extractor:

**************
API Extractor
**************

Overview
========

The **API Extractor** library is used by the binding generator to
parse the header and typesystem files to create an internal
representation of the API. It is based on the
`QtScriptGenerator <http://labs.trolltech.com/page/Projects/QtScript/Generator>`_
codebase.

Getting the sources
===================

* Download URL: http://www.pyside.org/downloads/

Build requirements
==================

+ CMake >= 2.6.0
+ Qt4.5 libraries and development headers >= 4.5.0

Building and installing
=======================

To build and install just follow the generic cmake instructions in section
:ref:`cmake-primer`.

Debian packaging
================

In order to compile this package in a debian environment, make sure the
following packages are installed:

* debhelper (>= 5)
* cdbs
* cmake (>= 2.6.0)
* libqt4-dev (>= 4.5)

And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
