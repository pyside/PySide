
.. _api-extractor:

**************
API Extractor
**************

Overview
========

The **API Extractor** library is used by the bindings generator to
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
+ Qt4.5 libraries and development headers >= 4.5
+ libxml2 libraries and development headers >= 2.6.32
+ libxslt libraries and development headers >= 1.1.19

Building and installing
=======================

To build and install just follow the generic CMake instructions in section
:ref:`cmake-primer`.

Debian packaging
================

In order to compile this package in a Debian environment, make sure the
following packages are installed:

* debhelper (>= 7)
* cmake (>= 2.6.0)
* libqt4-dev (>= 4.5)
* libxml2-dev
* libxslt1-dev
* pkg-config
* python-sphinx

And then you can build the package using::

  $ dpkg-buildpackage -rfakeroot
