OpenGL is a standard API for rendering 3D graphics. OpenGL only deals with 3D rendering and provides little or no support for GUI programming issues. The user interface for an OpenGL application must be created with another toolkit, such as Motif on the X platform, Microsoft Foundation Classes (MFC) under Windows, or Qt on both platforms.

.. note:: OpenGL is a trademark of Silicon Graphics, Inc. in the United States and other countries.

The Qt OpenGL module makes it easy to use OpenGL in Qt applications. It provides an OpenGL widget class that can be used just like any other Qt widget, except that it opens an OpenGL display buffer where you can use the OpenGL API to render the contents.
To include the definitions of the module's classes, use the following directive:

::

    import PySide.QtOpenGL

The Qt OpenGL module is implemented as a platform-independent wrapper around the platform-dependent GLX (version 1.3 or later), WGL, or AGL C APIs. Although the basic functionality provided is very similar to Mark Kilgard's GLUT library, applications using the Qt OpenGL module can take advantage of the whole Qt API for non-OpenGL-specific GUI functionality.

The QtOpenGL module is available on Windows, X11 and Mac OS X. Qt for Embedded Linux and OpenGL supports OpenGL ES (OpenGL for Embedded Systems).