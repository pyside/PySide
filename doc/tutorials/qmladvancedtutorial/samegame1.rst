.. _samegame1:

QML Advanced Tutorial 1 - Creating the Game Canvas and Blocks
*************************************************************

Creating the application screen
===============================

The first step is to create the basic QML items in your application.

To begin with, we create our Same Game application with a main screen like this:

.. figure:: declarative-adv-tutorial1.png
    :align: center

This is defined by the main application file, ``samegame.qml``, which looks like this:

.. pysideinclude:: samegame/samegame1/samegame.qml
    :snippet: 0

This gives you a basic game window that includes the main canvas for the
blocks, a "New Game" button and a score display.

One item you may not recognize here
is the SystemPalette item. This provides access to the Qt system palette
and is used to give the button a more native look-and-feel.

Notice the anchors for the ``Item``, ``Button`` and ``Text`` elements are set using
group notation for readability.

Adding Button and Block components
==================================

The ``Button`` item in the code above is defined in a separate component file named ``Button.qml``.
To create a functional button, we use the QML elements Text and MouseArea inside a Rectangle.
Here is the ``Button.qml`` code:

.. pysideinclude:: samegame/samegame1/Button.qml
    :snippet: 0

This essentially defines a rectangle that contains text and can be clicked. The MouseArea
has an ``onClicked()`` handler that is implemented to emit the ``clicked()`` signal of the
``container`` when the area is clicked.

In Same Game, the screen is filled with small blocks when the game begins.
Each block is just an item that contains an image. The block
code is defined in a separate ``Block.qml`` file:

.. pysideinclude:: samegame/samegame1/Block.qml
    :snippet: 0

At the moment, the block doesn't do anything; it is just an image. As the
tutorial progresses we will animate and give behaviors to the blocks.
We have not added any code yet to create the blocks; we will do this
in the next chapter.

We have set the image to be the size of its parent Item using ``anchors.fill: parent``.
This means that when we dynamically create and resize the block items
later on in the tutorial, the image will be scaled automatically to the
correct size.

Notice the relative path for the Image element's ``source`` property.
This path is relative to the location of the file that contains the Image element.
Alternatively, you could set the Image source to an absolute file path or a URL
that contains an image.

You should be familiar with the code so far. We have just created some basic
elements to get started. Next, we will populate the game canvas with some blocks.

[Previous :ref:`qmladvancedtutorial`] [Next :ref:`samegame2`]