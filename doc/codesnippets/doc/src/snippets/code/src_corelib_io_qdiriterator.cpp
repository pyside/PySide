//! [0]
it = QDirIterator("/etc", QDirIterator.Subdirectories)
while it.hasNext():
    print it.next()

    # /etc/.
    # /etc/..
    # /etc/X11
    # /etc/X11/fs
    # ...

//! [0]
