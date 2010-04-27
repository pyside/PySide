//! [0]
# To find the IP address of qtsoftware.com
QHostInfo.lookupHost("qtsoftware.com", self, SLOT("printResults(QHostInfo)"))

# To find the host name for 4.2.2.1
QHostInfo.lookupHost("4.2.2.1", self, SLOT("printResults(QHostInfo)"))
//! [0]


//! [1]
info = QHostInfo.fromName("qtsoftware.com")
//! [1]


//! [2]
QHostInfo.lookupHost("www.kde.org", self.lookedUp)
//! [2]


//! [3]
def lookedUp(host):
    if host.error() != QHostInfo.NoError:
        print "Lookup failed: %s" % host.errorString()
        return

    for address in host.addresses():
        print "Found address: %s" % address.toString()
//! [3]


//! [4]
QHostInfo.lookupHost("4.2.2.1", self.lookedUp)
//! [4]


//! [5]
info = QHostInfo()
...
if not info.addresses().isEmpty():
    address = info.addresses().first()
    # use the first IP address
//! [5]
