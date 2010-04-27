//! [0]
class HelloWorldTask(QRunnable):
    def run(self):
        print "Hello world from thread", QThread.currentThread()

hello = HelloWorldTask()
# QThreadPool takes ownership and deletes 'hello' automatically
QThreadPool.globalInstance()->start(hello)
//! [0]
