QtWebKit provides a Web browser engine that makes it easy to embed content from the World Wide Web into your Qt application. At the same time Web content can be enhanced with native controls.

QtWebKit provides facilities for rendering of HyperText Markup Language (HTML), Extensible HyperText Markup Language (XHTML) and Scalable Vector Graphics (SVG) documents, styled using Cascading Style Sheets (CSS) and scripted with JavaScript.

A bridge between the JavaScript execution environment and the Qt object model makes it possible for custom QObjects to be scripted. Integration with the Qt networking module enables Web pages to be transparently loaded from Web servers, the local file system or even the Qt resource system.

In addition to providing pure rendering features, HTML documents can be made fully editable to the user through the use of the contenteditable attribute on HTML elements.

QtWebKit is based on the Open Source WebKit engine. More information about WebKit itself can be found on the _`WebKit Open Source Project <http://webkit.org/>` Web site.

Including In Your Project
-------------------------

To include the definitions of the module's classes, use the following directive:

::

    import PySide.QtWebKit


.. note:: Web site icons, also known as "FavIcons", are currently not supported on Windows. We plan to address this in a future release.

Architecture
------------

The easiest way to render content is through the QWebView class. As a widget it can be embedded into your forms or a graphics view, and it provides convenience functions for downloading and rendering web sites.

::

    view = QWebView(parent)
    view.load(QUrl("http://qt.nokia.com/"))
    view.show()

QWebView is used to view Web pages. An instance of QWebView has one QWebPage. QWebPage provides access to the document structure in a page, describing features such as frames, the navigation history, and the undo/redo stack for editable content.

HTML documents can be nested using frames in a frameset. An individual frame in HTML is represented using the QWebFrame class. This class includes the bridge to the JavaScript window object and can be painted using QPainter. Each QWebPage has one QWebFrame object as its main frame, and the main frame may contain many child frames.

Individual elements of an HTML document can be accessed via DOM JavaScript interfaces from within a web page. The equivalent of this API in QtWebKit is represented by QWebElement. QWebElement objects are obtained using QWebFrame's findAllElements() and findFirstElement() functions with CSS selector queries.

Common web browser features, defaults and other settings can be configured through the QWebSettings class. It is possible to provide defaults for all QWebPage instances through the default settings. Individual attributes can be overidden by the page specific settings object.

Netscape Plugin Support
-----------------------

.. note:: Netscape plugin support is only available on desktop platforms.

Since WebKit supports the Netscape Plugin API, Qt applications can display Web pages that embed common plugins on platforms for which those plugins are available. To enable plugin support, the user must have the appropriate binary files for those plugins installed and the ``QWebSettings.PluginsEnabled`` attribute must be enabled for the application.

The following locations are searched for plugins:

* Linux/Unix (X11)
    * .mozilla/plugins in the user's home directory
    * .netscape/plugins in the user's home directory
    * System locations, such as
        * /usr/lib/browser/plugins
        * /usr/local/lib/mozilla/plugins
        * /usr/lib/firefox/plugins
        * /usr/lib64/browser-plugins
        * /usr/lib/browser-plugins
        * /usr/lib/mozilla/plugins
        * /usr/local/netscape/plugins
        * /opt/mozilla/plugins
        * /opt/mozilla/lib/plugins
        * /opt/netscape/plugins
        * /opt/netscape/communicator/plugins
        * /usr/lib/netscape/plugins
        * /usr/lib/netscape/plugins-libc5
        * /usr/lib/netscape/plugins-libc6
        * /usr/lib64/netscape/plugins
        * /usr/lib64/mozilla/plugins
    * Locations specified by environment variables:
        * $MOZILLA_HOME/plugins
        * $MOZ_PLUGIN_PATH
        * $QTWEBKIT_PLUGIN_PATH
* Windows
    * The user's Application Data\Mozilla\plugins directory
    * Standard system locations of plugins for Quicktime, Flash, etc.
* Mac OS X
    * Library/Internet Plug-Ins in the user's home directory
    * The system /Library/Internet Plug-Ins directory

License Information
-------------------

Qt Commercial Edition licensees that wish to distribute applications that use the QtWebKit module need to be aware of their obligations under the GNU Library General Public License (LGPL).

Developers using the Open Source Edition can choose to redistribute the module under the appropriate version of the GNU LGPL.
WebKit is licensed under the GNU Library General Public License. Individual contributor names and copyright dates can be found inline in the code.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Library General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Library General Public License for more details.

You should have received a copy of the GNU Library General Public License along with this library; see the file COPYING.LIB. If not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.