
def validateFromUrl():
//! [0]
    schema = getSchema()

    url = QUrl("http://www.schema-example.org/test.xml")

    validator = QXmlSchemaValidator(schema)
    if validator.validate(url):
        print "instance document is valid"
    else:
        print "instance document is invalid"
//! [0]

def validateFromFile():
//! [1]
    schema = getSchema()

    file = QFile("test.xml")
    file.open(QIODevice.ReadOnly)

    validator = QXmlSchemaValidator(schema)
    if validator.validate(file, QUrl.fromLocalFile(file.fileName())):
        print "instance document is valid"
    else:
        print "instance document is invalid"
//! [1]
}

def validateFromData():
//! [2]
    schema = getSchema()

    data = QByteArray("<?xml version=\"1.0\" encoding=\"UTF-8\"?><test></test>")

    buffer = QBuffer(data)
    buffer.open(QIODevice.ReadOnly)

    QXmlSchemaValidator validator(schema)
    if validator.validate(buffer):
        print "instance document is valid"
    else:
        print "instance document is invalid"
//! [2]

def validateComplete():
//! [3]
    schemaUrl = QUrl("file:///home/user/schema.xsd")

    schema = QXmlSchema()
    schema.load(schemaUrl)

    if schema.isValid():
        file = QFile("test.xml")
        file.open(QIODevice.ReadOnly)

        validator = QXmlSchemaValidator(schema)
        if validator.validate(file, QUrl.fromLocalFile(file.fileName())):
            print "instance document is valid"
        else:
            print "instance document is invalid"
    }
//! [3]
