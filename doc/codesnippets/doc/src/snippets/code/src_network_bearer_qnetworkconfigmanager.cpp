//! [0]
mgr = QNetworkConfigurationManager()
activeConfigs = mgr.allConfigurations(QNetworkConfiguration.Active)
if activeConfigs:
    assert(mgr.isOnline())
else:
    assert(not mgr.isOnline())
//! [0]
