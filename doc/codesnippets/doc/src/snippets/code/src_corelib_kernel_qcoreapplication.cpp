//! [0]
event = QMouseEvent(QEvent.MouseButtonPress, pos, 0, 0, 0)
QApplication.sendEvent(mainWindow, event)
//! [0]


//! [1]
quitButton = QPushButton("Quit")
quitButton.clicked.connect(app.quit)
//! [1]


//! [2]
for path in app.libraryPaths():
    do_something(path)
//! [2]


//! [3]
myEventFilter(message, result)
//! [3]


//! [4]
def cleanup_stuff():
    # do the cleanup stuff

def init_stuff():
    qAddPostRoutine(cleanup_stuff)
//! [4]


//! [5]
class MyPrivateInitStuff : public QObject
{
public:
    static MyPrivateInitStuff *initStuff(QObject *parent)
    {
        if (!p)
            p = new MyPrivateInitStuff(parent);
        return p;
    }

    ~MyPrivateInitStuff()
    {
        // cleanup goes here
    }

private:
    MyPrivateInitStuff(QObject *parent)
        : QObject(parent)
    {
        // initialization goes here
    }

    MyPrivateInitStuff *p;
};
//! [5]


//! [6]
static inline QString tr(const char *sourceText,
                         const char *comment = 0);
static inline QString trUtf8(const char *sourceText,
                             const char *comment = 0);
//! [6]


//! [7]
class MyMfcView : public CView
{
    Q_DECLARE_TR_FUNCTIONS(MyMfcView)

public:
    MyMfcView();
    ...
};
//! [7]
