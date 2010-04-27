//! [0]
xml = QXmlStreamReader()
...
while not xml.atEnd():
    xml.readNext();
    ... # do processing

if xml.hasError():
    ... # do error handling

//! [0]


//! [1]
writeStartElement(qualifiedName)
writeCharacters(text)
writeEndElement()
//! [1]


//! [2]
writeStartElement(namespaceUri, name)
writeCharacters(text)
writeEndElement()
//! [2]


