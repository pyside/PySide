//! [0]
manager = QNetworkAccessManager(self)
manager.finished[QNetworkReply].connect(self.replyFinished)

manager.get(QNetworkRequest(QUrl("http://qt.nokia.com")))
//! [0]


//! [1]
request = QNetworkRequest()
request.setUrl(QUrl("http://qt.nokia.com"))
request.setRawHeader("User-Agent", "MyOwnBrowser 1.0")

reply = manager.get(request)
reply.readyRead.connect(self.slotReadyRead)
reply.error[QNetworkReply.NetworkError].connect(self..slotError)
reply.sslErrors.connect(self.slotSslErrors)
//! [1]

//! [2]
manager = QNetworkConfigurationManager()
networkAccessManager.setConfiguration(manager.defaultConfiguration())
//! [2]

//! [3]
networkAccessManager.setConfiguration(QNetworkConfiguration())
//! [3]

//! [4]
networkAccessManager.setNetworkAccessible(QNetworkAccessManager.NotAccessible)
//! [4]

//! [5]
networkAccessManager.setNetworkAccessible(QNetworkAccessManager.Accessible)
//! [5]

