.. _qmlbasictypes:

QML Tutorial 1 - Basic Types
****************************

This first program is a very simple "Hello world" example that introduces some basic QML concepts.
The picture below is a screenshot of this program.

.. figure:: declarative-tutorial1.png
    :align: center

Here is the QML code for the application:

.. pysideinclude:: helloworld/tutorial1.qml
    :snippet: 0

Walkthrough
===========

Import
------

First, we need to import the types that we need for this example. Most QML files will import the built-in QML
types (like Rectangle, Image, ...) that come with Qt, using:

.. pysideinclude:: helloworld/tutorial1.qml
    :snippet: 3

Rectangle element
-----------------

.. pysideinclude:: helloworld/tutorial1.qml
    :snippet: 1

We declare a root element of type Rectangle. It is one of the basic building blocks you can use to create an application in QML.
We give it an ``id`` to be able to refer to it later. In this case, we call it "page".
We also set the ``width``, ``height`` and ``color`` properties.
The Rectangle element contains many other properties (such as ``x`` and ``y``), but these are left at their default values.

Text element
------------

.. pysideinclude code/tutorial1.qml
    :snippet: 2

We add a Text element as a child of the root Rectangle element that displays the text 'Hello world!'.

The ``y`` property is used to position the text vertically at 30 pixels from the top of its parent.

The ``anchors.horizontalCenter`` property refers to the horizontal center of an element.
In this case, we specify that our text element should be horizontally centered in the *page* element.

The ``font.pointSize`` and ``font.bold properties`` are related to fonts and use the dot notation.


Viewing the example
-------------------

To view what you have created, run the QML Viewer tool (located in the ``bin directory`` of your Qt installation) with your filename as the first argument.
For example, to run the provided completed Tutorial 1 example from the install location, you would type:

::

    bin/qmlviewer tutorial1.qml

[Previous :ref:`qmltutorial`][Next :ref:`qmlcomponents`]
