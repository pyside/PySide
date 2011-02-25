.. _samegame2:

QML Advanced Tutorial 2 - Populating the Game Canvas
****************************************************

Generating the blocks in JavaScript
===================================

Now that we've written some basic elements, let's start writing the game.

The first task is to generate the game blocks. Each time the New Game button
is clicked, the game canvas is populated with a new, random set of
blocks. Since we need to dynamically generate new blocks for each new game,
we cannot use Repeater to define the blocks. Instead, we will
create the blocks in JavaScript.

Here is the JavaScript code for generating the blocks, contained in a new
file, ``samegame.js``. The code is explained below.

.. pysideinclude:: samegame/samegame2/samegame.js
    :snippet: 0

The ``startNewGame()`` function deletes the blocks created in the previous game and
calculates the number of rows and columns of blocks required to fill the game window for the new game.
Then, it creates an array to store all the game
blocks, and calls ``createBlock()`` to create enough blocks to fill the game window.

The ``createBlock()`` function creates a block from the ``Block.qml`` file
and moves the new block to its position on the game canvas. This involves several steps:

*  ``Qt.createComponent()`` is called to
   generate an element from ``Block.qml``.  If the component is ready,
   we can call ``createObject()`` to create an instance of the ``Block``
   item.

*  If ``createObject()`` returned null (i.e. if there was an error
   while loading the object), print the error information.

*  Place the block in its position on the board and set its width and
   height.  Also, store it in the blocks array for future reference.

*  Finally, print error information to the console if the component
   could not be loaded for some reason (for example, if the file is
   missing).

Connecting JavaScript components to QML
=======================================

Now we need to call the JavaScript code in ``samegame.js`` from our QML files.
To do this, we add this line to ``samegame.qml`` which imports
the JavaScript file as a module:

.. pysideinclude:: samegame/samegame2/samegame.qml
    :snippet: 2

This allows us to refer to any functions within ``samegame.js`` using "SameGame"
as a prefix: for example, ``SameGame.startNewGame()`` or ``SameGame.createBlock()``.
This means we can now connect the New Game button's ``onClicked`` handler to the ``startNewGame()``
function, like this:

.. pysideinclude:: samegame/samegame2/samegame.qml
    :snippet: 1

So, when you click the New Game button, ``startNewGame()`` is called and generates a field of blocks, like this:

.. figure:: declarative-adv-tutorial2.png
    :align: center

Now, we have a screen of blocks, and we can begin to add the game mechanics.

[Previous :ref:`samegame1`] [Next :ref:`samegame3`]