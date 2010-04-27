//! [0]
content-type: text/html
//! [0]


//! [1]
header.setValue("content-type", "text/html")
contentType = header.value("content-type")
//! [1]


//! [2]
header = QHttpRequestHeader("GET", QUrl.toPercentEncoding("/index.html"))
header.setValue("Host", "qtsoftware.com")
http.setHost("qtsoftware.com")
http.request(header)
//! [2]


//! [3]
http.setHost("qtsoftware.com")                  # id == 1
http.get(QUrl.toPercentEncoding("/index.html")) # id == 2
//! [3]


//! [4]
requestStarted(1)
requestFinished(1, False)

requestStarted(2)
stateChanged(Connecting)
stateChanged(Sending)
dataSendProgress(77, 77)
stateChanged(Reading)
responseHeaderReceived(responseheader)
dataReadProgress(5388, 0)
readyRead(responseheader)
dataReadProgress(18300, 0)
readyRead(responseheader)
stateChanged(Connected)
requestFinished(2, False)

done(False)

stateChanged(Closing)
stateChanged(Unconnected)
//! [4]


//! [5]
http.setHost("www.foo.bar")       # id == 1
http.get("/index.html")           # id == 2
http.post("register.html", data)  # id == 3
//! [5]


//! [6]
requestStarted(1)
requestFinished(1, False)

requestStarted(2)
stateChanged(HostLookup)
requestFinished(2, True)

done(True)

stateChanged(Unconnected)
//! [6]


//! [7]
def getTicks(self):
  http = QHttp(self)
  self.connect(http, SIGNAL('done(bool)'), self, SLOT('showPage()'))
  http.setProxy("proxy.example.com", 3128)
  http.setHost("ticker.example.com")
  http.get("/ticks.asp")

def showPage(self):
  self.display(http.readAll())

//! [7]
