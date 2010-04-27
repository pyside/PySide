//! [0]
def showHelp(url):
    # ...
    pass

QDesktopServices.setUrlHandler("help", showHelp);
//! [0]

//! [1]
mailto:user@foo.com?subject=Test&body=Just a test
//! [1]

//! [2]
QDesktopServices.openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl.TolerantMode))
//! [2]
