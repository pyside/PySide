//! [0]
manager = QNetworkAccessManager(self)
diskCache = QNetworkDiskCache(self)
diskCache.setCacheDirectory("cacheDir")
manager.setCache(diskCache)
//! [0]

//! [1]
# do a normal request (preferred from network, as this is the default)
request = QNetworkRequest(QUrl("http://qt.nokia.com"))
manager.get(request)

# do a request preferred from cache
request2 = QNetworkRequest(QUrl("http://qt.nokia.com"))
request2.setAttribute(QNetworkRequest.CacheLoadControlAttribute, QNetworkRequest.PreferCache)
manager.get(request2)
//! [1]

//! [2]
@Slot(QNetworkReply)
def replyFinished(reply):
    fromCache = reply.attribute(QNetworkRequest.SourceIsFromCacheAttribute)
    print("page from cache? %d" % fromCache)
//! [2]
