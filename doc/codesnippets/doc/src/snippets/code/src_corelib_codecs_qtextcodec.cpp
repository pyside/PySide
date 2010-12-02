//! [0]
encodedString = QByteArray("...")
codec = QTextCodec.codecForName("KOI8-R")
string = codec.toUnicode(encodedString)
//! [0]


//! [1]
string = u"..."
codec = QTextCodec.codecForName("KOI8-R")
encodedString = codec.fromUnicode(string)
//! [1]


//! [2]
codec = QTextCodec.codecForName("Shift-JIS")
decoder = codec.makeDecoder()

string = u''
while new_data_available():
    chunk = get_new_data()
    string += decoder.toUnicode(chunk)

//! [2]


//! [3]
def main():
    app = QApplication([])
    QTextCodec.setCodecForTr(QTextCodec.codecForName("eucKR"))
    ...
//! [3]
