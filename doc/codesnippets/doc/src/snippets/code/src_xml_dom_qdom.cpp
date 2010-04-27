//! [0]
doc = QDomDocument()
impl = QDomImplementation()

# This will create the element, but the resulting XML document will
# be invalid, because '~' is not a valid character in a tag name.
impl.setInvalidDataPolicy(QDomImplementation.AcceptInvalidData)
elt1 = doc.createElement("foo~bar")

# This will create an element with the tag name "foobar".
impl.setInvalidDataPolicy(QDomImplementation.DropInvalidData)
elt2 = doc.createElement("foo~bar")

# This will create a null element.
impl.setInvalidDataPolicy(QDomImplementation::ReturnNullNode)
elt3 = doc.createElement("foo~bar")
//! [0]


//! [1]
d = QDomDocument()
d.setContent(someXML)
n = d.firstChild()
while !n.isNull():
    if n.isElement():
        e = n.toElement()
        print "Element name: %s" % e.tagName()
        break
    n = n.nextSibling()
//! [1]


//! [2]
QDomDocument document
QDomElement element1 = document.documentElement()
QDomElement element2 = element1
//! [2]


//! [3]
QDomElement element3 = document.createElement("MyElement")
QDomElement element4 = document.createElement("MyElement")
//! [3]


//! [4]
<body>
<h1>Heading</h1>
<p>Hello <b>you</b></p>
</body>
//! [4]


//! [5]
<h1>Heading</h1>
<p>The text...</p>
<h2>Next heading</h2>
//! [5]


//! [6]
<h1>Heading</h1>
<p>The text...</p>
<h2>Next heading</h2>
//! [6]


//! [7]
<link href="http://qtsoftware.com" color="red" />
//! [7]


//! [8]
e = # some QDomElement...
#...
a = e.attributeNode("href")
print a.value()                         # prints "http://qtsoftware.com"
a.setValue("http://doc.trolltech.com")  # change the node's attribute
a2 = e.attributeNode("href")
print a2.value()                        # prints "http://doc.trolltech.com"
//! [8]


//! [9]
e = # some QDomElement...
#...
s = e.text()
//! [9]


//! [10]
text = QString()
element = doc.documentElement()

n = element.firstChild()
while True:
    if not n.isNull()
        break
    t = n.toText()
    if !t.isNull():
        text += t.data()

    n = n.nextSibling()
//! [10]


//! [11]
doc = # some QDomDocument ...
root = doc.firstChildElement("database")
elt = root.firstChildElement("entry")
while True:
    if not elt.isNull():
        break
    # ...
    elt = elt.nextSiblingElement("entry")
//! [11]


//! [12]
<img src="myimg.png">
//! [12]


//! [13]
<h1>Hello <b>Qt</b> <![CDATA[<xml is cool>]]></h1>
//! [13]


//! [14]
Hello Qt <xml is cool>
//! [14]


//! [15]
<!-- this is a comment -->
//! [15]


//! [16]
doc = QDomDocument("mydocument")
file = QFile("mydocument.xml")
if not file.open(QIODevice::ReadOnly):
    return
if not doc.setContent(&file):
    file.close()
    return
file.close()

# print out the element names of all elements that are direct children
# of the outermost element.
docElem = doc.documentElement()

n = docElem.firstChild()
while not n.isNull():
    e = n.toElement() # try to convert the node to an element.
    if not e.isNull():
        print e.tagName() # the node really is an element.
    n = n.nextSibling()
}

# Here we append a new element to the end of the document
elem = doc.createElement("img")
elem.setAttribute("src", "myimage.png")
docElem.appendChild(elem)
//! [16]


//! [17]
doc = QDomDocument("MyML")
root = doc.createElement("MyML")
doc.appendChild(root)

tag = doc.createElement("Greeting")
root.appendChild(tag)

t = doc.createTextNode("Hello World")
tag.appendChild(t)

xml = doc.toString()
//! [17]
