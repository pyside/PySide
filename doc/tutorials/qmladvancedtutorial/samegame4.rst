.. _samegame4:

QML Advanced Tutorial 4 - Finishing Touches
*******************************************

Adding some flair
=================

Now we're going to do two things to liven up the game: animate the blocks and add a High Score system.

We've also cleaned up the directory structure for our application files. We now have a lot of files, so all the
JavaScript and QML files outside of ``samegame.qml`` have been moved into a new sub-directory named "content".

In anticipation of the new block animations, ``Block.qml`` file is now renamed to ``BoomBlock.qml``.

Animating block movement
------------------------

First we will animate the blocks so that they move in a fluid manner. QML has a number of methods for adding fluid
movement, and in this case we're going to use the Behavior element to add a SpringAnimation.
In ``BoomBlock.qml``, we apply a SpringAnimation behavior to the ``x`` and ``y`` properties so that the
block will follow and animate its movement in a spring-like fashion towards the specified position (whose
values will be set by ``samegame.js``).Here is the code added to ``BoomBlock.qml``:

.. pysideinclude:: samegame/samegame4/content/BoomBlock.qml
    :snippet: 1

The ``spring`` and ``damping`` values can be changed to modify the spring-like effect of the animation.

The ``enabled: spawned`` setting refers to the ``spawned`` value that is set from ``createBlock()`` in ``samegame.js``.
This ensures the SpringAnimation on the ``x`` is only enabled after ``createBlock()`` has set the block to
the correct position. Otherwise, the blocks will slide out of the corner (0,0) when a game begins, instead of falling
from the top in rows. (Try commenting out ``enabled: spawned`` and see for yourself.)

Animating block opacity changes
-------------------------------

Next, we will add a smooth exit animation. For this, we'll use a Behavior element, which allows us to specify
a default animation when a property change occurs. In this case, when the ``opacity`` of a Block changes, we will
animate the opacity value so that it gradually fades in and out, instead of abruptly changing between fully
visible and invisible. To do this, we'll apply a Behavior on the ``opacity`` property of the ``Image``
element in ``BoomBlock.qml``:

.. pysideinclude:: samegame/samegame4/content/BoomBlock.qml
    :snippet: 2

Note the ``opacity: 0`` which means the block is transparent when it is first created. We could set the opacity
in ``samegame.js`` when we create and destroy the blocks,
but instead we'll use states, since this is useful for the next animation we're going to add.
Initially, we add these States to the root element of ``BoomBlock.qml``:

::

    property bool dying: false
    states: [
        State{ name: "AliveState"; when: spawned == true && dying == false
            PropertyChanges { target: img; opacity: 1 }
        },
        State{ name: "DeathState"; when: dying == true
            PropertyChanges { target: img; opacity: 0 }
        }
    ]

Now blocks will automatically fade in, as we already set ``spawned`` to true when we implemented the block animations.
To fade out, we set ``dying`` to true instead of setting opacity to 0 when a block is destroyed (in the ``floodFill()`` function).

Adding particle effects
-----------------------

Finally, we'll add a cool-looking particle effect to the blocks when they are destroyed. To do this, we first add a Particles element in
``BoomBlock.qml``, like so:

.. pysideinclude:: samegame/samegame4/content/BoomBlock.qml
    :snippet: 3

To fully understand this you should read the Particles documentation, but it's important to note that ``emissionRate`` is set
to zero so that particles are not emitted normally.
Also, we extend the ``dying`` State, which creates a burst of particles by calling the ``burst()`` method on the particles element. The code for the states now look
like this:

.. pysideinclude:: samegame/samegame4/content/BoomBlock.qml
    :snippet: 4

Now the game is beautifully animated, with subtle (or not-so-subtle) animations added for all of the
player's actions. The end result is shown below, with a different set of images to demonstrate basic theming:

.. figure:: declarative-adv-tutorial4.gif
    :align: center

The theme change here is produced simply by replacing the block images. This can be done at runtime by changing the \l Image \c source property, so for a further challenge, you could add a button that toggles between themes with different images.

Keeping a High Scores table
===========================

Another feature we might want to add to the game is a method of storing and retrieving high scores.

To do this, we will show a dialog when the game is over to request the player's name and add it to a High Scores table.
This requires a few changes to ``Dialog.qml``. In addition to a ``Text`` element, it now has a
``TextInput`` child item for receiving keyboard text input:

.. pysideinclude:: samegame/samegame4/content/Dialog.qml
    :snippet: 2
    :prepend: Rectangle {
              ...
    :append: ...
             }


We'll also add a ``showWithInput()`` function. The text input will only be visible if this function
is called instead of ``show()``. When the dialog is closed, it emits a ``closed()`` signal, and
other elements can retrieve the text entered by the user through an ``inputText`` property:

.. pysideinclude:: samegame/samegame4/content/Dialog.qml
    :snippet: 1
    :prepend: Rectangle {
              ...
    :append: ...
             }

Now the dialog can be used in ``samegame.qml``:

.. pysideinclude:: samegame/samegame4/samegame.qml
    :snippet: 0

When the dialog emits the ``closed`` signal, we call the new ``saveHighScore()`` function in ``samegame.js``, which stores the high score locally in an SQL database and also send the score to an online database if possible.

The ``nameInputDialog`` is activated in the ``victoryCheck()`` function in ``samegame.js``:

.. pysideinclude:: samegame/samegame4/content/samegame.js
    :snippet: 4
    :prepend: function vitoryCheck() {
              ...

Storing high scores offline
---------------------------

Now we need to implement the functionality to actually save the High Scores table.

Here is the ``saveHighScore()`` function in ``samegame.js``:

.. pysideinclude:: samegame/samegame4/content/samegame.js
    :snippet: 2

First we call ``sendHighScore()`` (explained in the section below) if it is possible to send the high scores to an online database.

Then, we use the Offline Storage API to maintain a persistant SQL database unique to this application. We create an offline storage database for the high scores using ``openDatabase()`` and prepare the data and SQL query that we want to use to save it. The offline storage API uses SQL queries for data manipulation and retrival, and in the ``db.transaction()`` call we use three SQL queries to initialize the database (if necessary), and then add to and retrieve high scores. To use the returned data, we turn it into a string with one line per row returned, and show a dialog containing that string.

This is one way of storing and displaying high scores locally, but certainly not the only way. A more complex alternative would be to create a high score dialog component, and pass it the results for processing and display (instead of reusing the ``Dialog``). This would allow a more themeable dialog that could beter present the high scores. If your QML is the UI for a Python application, you could also have passed the score to a Python function to store it locally in a variety of ways, including a simple format without SQL or in another SQL database.

Storing high scores online
--------------------------

You've seen how you can store high scores locally, but it is also easy to integrate a web-enabled high score storage into your QML application. The implementation we've done here is very
simple: the high score data is posted to a php script running on a server somewhere, and that server then stores it and
displays it to visitors. You could also request an XML or QML file from that same server, which contains and displays the scores,
but that's beyond the scope of this tutorial. The php script we use here is available in the ``examples`` directory.

If the player entered their name we can send the data to the web service us

If the player enters a name, we send the data to the service using this code in ``samegame.js``:

.. pysideinclude:: samegame/samegame4/content/samegame.js
    :snippet: 1

The XMLHttpRequest in this code is the same as the ``XMLHttpRequest()`` as you'll find in standard browser JavaScript, and can be used in the same way to dynamically get XML
or QML from the web service to display the high scores. We don't worry about the response in this case - we just post the high
score data to the web server. If it had returned a QML file (or a URL to a QML file) you could instantiate it in much the same
way as you did with the blocks.

An alternate way to access and submit web-based data would be to use QML elements designed for this purpose. XmlListModel
makes it very easy to fetch and display XML based data such as RSS in a QML application (see the Flickr demo for an example).


That's it!
==========

By following this tutorial you've seen how you can write a fully functional application in QML:

* Build your application with QML elements.
* Add application logic with JavaScript code.
* Add animations with Behaviors and states.
* Store persistent application data using, for example, the Offline Storage API or XMLHttpRequest.

There is so much more to learn about QML that we haven't been able to cover in this tutorial. Check out all the
demos and examples and the documentation to see all the things you can do with QML!

[Previous :ref:`samegame3`]