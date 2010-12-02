//! [0]
url = QUrl("http://www.example.com/List of holidays.xml")
# url.toEncoded() == "http://www.example.com/List%20of%20holidays.xml"
//! [0]


//! [1]
url = QUrl.fromEncoded("http://qtsoftware.com/List%20of%20holidays.xml")
//! [1]


//! [2]
def checkUrl(url):
    if !url.isValid():
        print "Invalid URL: %s" % url.toString()
        return False

    return True

//! [2]


//! [3]
ftp = QFtp()
ftp.connectToHost(url.host(), url.port(21))
//! [3]


//! [4]
http://www.example.com/cgi-bin/drawgraph.cgi?type-pie/color-green
//! [4]


//! [5]
baseUrl = QUrl("http://qtsoftware.com/support")
relativeUrl = QUrl("../products/solutions")
print baseUrl.resolved(relativeUrl).toString()
# prints "http://qtsoftware.com/products/solutions"
//! [5]


//! [6]
ba = QUrl.toPercentEncoding("{a fishy string?}", "{}", "s")
print ba
# prints "{a fi%73hy %73tring%3F}"
//! [6]
