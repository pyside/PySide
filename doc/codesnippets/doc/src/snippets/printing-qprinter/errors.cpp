//! [0]
    printer = QPrinter()
    printer.setOutputFormat(QPrinter.PdfFormat)
    printer.setOutputFileName("/foobar/nonwritable.pdf")
    QPainter painter
    if painter.begin(printer):  # failed to open file
        print "failed to open file, is it writable?"
        return 1
    
    painter.drawText(10, 10, "Test")
    if !printer.Page():
        print "failed in flushing page to disk, disk full?"
        return 1
    
    painter.drawText(10, 10, "Test 2")
    painter.end()
//! [0]

