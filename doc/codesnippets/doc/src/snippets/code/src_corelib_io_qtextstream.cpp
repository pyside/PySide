//! [0]
data = QFile("output.txt")
if data.open(QFile.WriteOnly | QFile.Truncate):
    out = QTextStream(&data)
    out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7
    # writes "Result: 3.14      2.7       "

//! [0]


//! [1]
stream = QTextStream(sys.stdin.fileno())

while(True):
    line = stream.readLine()
    if line.isNull():
        break;
//! [1]


//! [2]
in_ = QTextStream("0x50 0x20")
firstNumber = 0
secondNumber = 0

in_ >> firstNumber             # firstNumber == 80
in_ >> dec >> secondNumber     # secondNumber == 0

ch = None
in_ >> ch                      # ch == 'x'
//! [2]


//! [3]
def main():
    # read numeric arguments (123, 0x20, 4.5...)
    for i in sys.argv():
          number = None
          QTextStream in_(i)
          in_ >> number
          ...
//! [3]


//! [4]
str = QString()
in_ = QTextStream(sys.stdin.fileno())
in_ >> str
//! [4]


//! [5]
s = QString()
out = QTextStream(s)
out.setFieldWidth(10)
out.setFieldAlignment(QTextStream::AlignCenter)
out.setPadChar('-')
out << "Qt" << "rocks!"
//! [5]


//! [6]
----Qt------rocks!--
//! [6]


//! [7]
in_ = QTextStream(file)
ch1 = QChar()
ch2 = QChar()
ch3 = QChar()
in_ >> ch1 >> ch2 >> ch3;
//! [7]


//! [8]
out = QTextStream(sys.stdout.fileno())
out << "Qt rocks!" << endl
//! [8]


//! [9]
stream << '\n' << flush
//! [9]


//! [10]
out = QTextStream(file)
out.setCodec("UTF-8")
//! [10]
