//! [0]
lineEdit = qt_find_obj_child(myWidget, "QLineEdit", "my line edit")
if lineEdit:
    lineEdit.setText("Default")
//! [0]


//! [1]
obj = QPushButton()
obj.metaObject().className()                # returns "QPushButton"

QPushButton.staticMetaObject.className()    # returns "QPushButton"
//! [1]


//! [2]
QPushButton.staticMetaObject.className()    # returns "QPushButton"

obj = QPushButton()
obj.metaObject().className()                # returns "QPushButton"
//! [2]


//! [3]
obj = QTimer()                              # QTimer inherits QObject

timer = obj
# timer == (QObject *)obj

button = obj
# button == 0
//! [3]


//! [4]
timer = QTimer()                    # QTimer inherits QObject
timer.inherits("QTimer")            # returns true
timer.inherits("QObject")           # returns true
timer.inherits("QAbstractButton")   # returns false

# QLayout inherits QObject and QLayoutItem
layout = QLayout()
layout.inherits("QObject")          # returns true
layout.inherits("QLayoutItem")      # returns false
//! [4]


//! [5]
print "MyClass::setPrecision(): (%s) invalid precision %f" % \
       (qPrintable(objectName()), newPrecision)
//! [5]


//! [6]
class MainWindow(QMainWindow):
    def __init__(self):
        self.textEdit = QTextEdit()
        setCentralWidget(self.textEdit)
        textEdit.installEventFilter(self)

    def eventFilter(self, obj, event):
        if obj == textEdit:
            if event.type() == QEvent.KeyPress:
                keyEvent = event
                print "Ate key press", keyEvent.key()
                return true
            else:
                return false
        else:
            # pass the event on to the parent class
            return QMainWindow.eventFilter(self, obj, event)
//! [6]


//! [7]
myObject.moveToThread(QApplication.instance().thread())
//! [7]


//! [8]
class MyObject(QObject):
    def __init__(self, parent):
        QObject.__init__(self, parent)

        self.startTimer(50)         # 50-millisecond timer
        self.startTimer(1000)       # 1-second timer
        self.startTimer(60000)      # 1-minute timer


    def timerEvent(self, event):
        print "Timer ID:", event.timerId()

//! [8]


//! [9]
list = window().queryList("QAbstractButton")
for obj in list:
    obj.setEnabled(false)
//! [9]


//! [10]
button = parentWidget.findChild(QPushButton, "button1")
//! [10]


//! [11]
list = parentWidget.findChild(QListWidget)
//! [11]


//! [12]
widgets = parentWidget.findChildren(QWidget, "widgetname")
//! [12]


//! [13]
allPButtons = parentWidget.findChildren(QPushButton)
//! [13]


//! [14]
monitoredObj.installEventFilter(filterObj)
//! [14]


//! [15]
class KeyPressEater(QObject):
    def eventFilter(self, obj, event):
        if event.type() == QEvent.KeyPress:
            print "Ate key press", event.key()
            return True
        else:
            # standard event processing
            return QObject.eventFilter(self, obj, event)
//! [15]


//! [16]
keyPressEater = KeyPressEater(self)
pushButton = QPushButton(self)
listView = QListView(self)

pushButton.installEventFilter(keyPressEater)
listView.installEventFilter(keyPressEater)
//! [16]


//! [17]
def __init__(self):
    senderLabel = QLabel(self.tr("Name:"))
    recipientLabel = QLabel(self.tr("Name:", "recipient"))
    # ...
//! [17]


//! [18]
n = messages.count();
showMessage(self.tr("%n message(s) saved", "", n));
//! [18]


//! [19]
if n == 1:
    self.tr("%n message saved")
else:
    self.tr("%n messages saved")
//! [19]


//! [20]
label.setText(self.tr("F\374r \310lise"))
//! [20]


//! [21]
if receivers(SIGNAL('valueChanged()')) > 0:
    data = get_the_value()  # expensive operation
    self.valueChanged(data)
//! [21]


//! [22]
label = QLabel()
scrollBar = QScrollBar()
QObject.connect(scrollBar, SIGNAL('valueChanged()'),
                label,  SLOT('setNum()'))
//! [22]


//! [23]
// WRONG
QObject.connect(scrollBar, SIGNAL('valueChanged()'),
                 label, SLOT('setNum()'));
//! [23]


//! [24]
class MyWidget(QWidget):
    def __init__(self):
        myButton = QPushButton(self)
        connect(myButton, SIGNAL('clicked()'),
                self, SIGNAL('buttonClicked()'))
//! [24]


//! [25]
QObject.connect: Cannot queue arguments of type 'MyType'
(Make sure 'MyType' is registered using qRegisterMetaType().)
//! [25]


//! [26]
disconnect(myObject, 0, 0, 0)
//! [26]


//! [27]
myObject.disconnect()
//! [27]


//! [28]
disconnect(myObject, SIGNAL('mySignal()'), 0, 0)
//! [28]


//! [29]
myObject.disconnect(SIGNAL('mySignal()'))
//! [29]


//! [30]
disconnect(myObject, 0, myReceiver, 0)
//! [30]


//! [31]
myObject.disconnect(myReceiver)
//! [31]


//! [32]
if QLatin1String(signal) == SIGNAL('valueChanged()'):
    # signal is valueChanged()
//! [32]


//! [33]
def on_<object name>_<signal name>(<signal parameters>)
//! [33]


//! [34]
def on_button1_clicked()
//! [34]


//! [35]
class MyClass(QObject):
    Q_CLASSINFO("Author", "Pierre Gendron")
    Q_CLASSINFO("URL", "http://www.my-organization.qc.ca")

//! [35]


//! [36]
Q_PROPERTY(type name
           READ getFunction
           [WRITE setFunction]
           [RESET resetFunction]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
	   [USER bool])
//! [36]


//! [37]
Q_PROPERTY(QString title READ title WRITE setTitle USER true)
//! [37]


//! [38]
#this not apply for Python
class MyClass(QObject):

    Q_OBJECT
    Q_ENUMS(Priority)

public:
    MyClass(QObject *parent = 0);
    ~MyClass();

    enum Priority { High, Low, VeryHigh, VeryLow };
    void setPriority(Priority priority);
    Priority priority() const;
};
//! [38]


//! [39]
#this not apply for Python
Q_FLAGS(Options Alignment)
//! [39]


//! [40]
//: This name refers to a host name.
hostNameLabel.setText(self.tr("Name:"))

#: This text refers to a C++ code example. 
example = self.tr("Example")
//! [40]

//! [explicit tr context]
text = QScrollBar.tr("Page up")
//! [explicit tr context]
