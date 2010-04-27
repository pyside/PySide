{
//! [0]
    # Within a function/method...

    file = QTemporaryFile()
    if file.open():
        # file.fileName() returns the unique file name

    # The QTemporaryFile destructor removes the temporary file
    # as it goes out of scope.
//! [0]
}
