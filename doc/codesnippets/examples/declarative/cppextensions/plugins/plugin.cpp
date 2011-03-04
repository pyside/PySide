
//![0]
class TimeModel (QObject):
    hour = Property(int, getHour, notify = timeChanged)
    minute = Property(int, getMinute, notify = timeChanged)
//![0]

//![plugin]
class QExampleQmlPlugin (QDeclarativeExtensionPlugin):

    def registerTypes(self, uri):
        assert(uri == "com.nokia.TimeExample")
        qmlRegisterType(TimeModel, uri, 1, 0, "Time")
//![plugin]

//![export]
# This isn't supported by PySide yet.
# Q_EXPORT_PLUGIN2(qmlqtimeexampleplugin, QExampleQmlPlugin);
//![export]
