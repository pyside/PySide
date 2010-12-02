{
//! [0]
    # Within a function/method...

    file_ = QTemporaryFile()
    if file_.open():
        # file_.fileName() returns the unique file name

    # The QTemporaryFile destructor removes the temporary file
    # as it goes out of scope.
//! [0]
}
