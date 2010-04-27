//! [0]
rx = QRegExp("(\\d+)")
txt = "Offsets: 12 14 99 231 7"
lst = []

pos = rx.indexIn(txt, 0)

while pos != -1:
    lst.append(rx.cap(1))
    pos += rx.matchedLength()
    pos = rx.indexIn(txt, pos)

# lst: ["12", "14", "99", "231", "7"]
//! [0]


//! [1]
rx = QRegExp("*.txt")
rx.setPatternSyntax(QRegExp.Wildcard)
rx.exactMatch("README.txt")        # returns True
rx.exactMatch("welcome.txt.bak")   # returns False
//! [1]


//! [2]
rx = QRegExp("ro+m")
rx.setMinimal(True)
//! [2]


//! [3]
mark = QRegExp("\\b"       # word boundary
               "[Mm]ark"   # the word we want to match
              )
//! [3]


//! [4]
rx = QRegExp("^\\d\\d?$")  # match integers 0 to 99
rx.indexIn("123")          # returns -1 (no match)
rx.indexIn("-6")           # returns -1 (no match)
rx.indexIn("6")            # returns  0 (matched as position 0)
//! [4]


//! [5]
rx = QRegExp("^\\S+$")     # match strings without whitespace
rx.indexIn("Hello world")  # returns -1 (no match)
rx.indexIn("This_is-OK")   # returns  0 (matched at position 0)
//! [5]


//! [6]
rx = QRegExp("\\b(mail|letter|correspondence)\\b")
rx.indexIn("I sent you an email")     # returns -1 (no match)
rx.indexIn("Please write the letter") # returns 17
//! [6]


//! [7]
captured = rx.cap(1) # captured == "letter"
//! [7]


//! [8]
rx = QRegExp("&(?!amp;)")                  # match ampersands but not &amp;
line1 = QString("This & that")
line1.replace(rx, "&amp;")                 # line1 == "This &amp; that"
line2 = QString("His &amp; hers & theirs")
line2.replace(rx, "&amp;")                 # line2 == "His &amp; hers &amp; theirs"
//! [8]


//! [9]
txt = QString("One Eric another Eirik, and an Ericsson. How many Eiriks, Eric?")
rx = QRegExp("\\b(Eric|Eirik)\\b")  # match Eric or Eirik
pos = 0                             # where we are in the string
count = 0                           # how many Eric and Eirik's we've counted

while pos >= 0:
    pos = rx.indexIn(txt, pos)
    if pos >= 0:
        pos += 1                    # move along in str
        count += 1                  # count our Eric or Eirik
//! [9]


//! [10]
txt = "Nokia Corporation and/or its subsidiary(-ies)\tqtsoftware.com\tNorway"
rx.setPattern("^([^\t]+)\t([^\t]+)\t([^\t]+)$");
if rx.indexIn(txt) != -1:
    company = rx.cap(1)
    web = rx.cap(2)
    country = rx.cap(3)
//! [10]


//! [11]
field = txt.split("\t")
//! [11]


//! [12]
rx = QRegExp("*.html")
rx.setPatternSyntax(QRegExp.Wildcard)
rx.exactMatch("index.html")             # returns True
rx.exactMatch("default.htm")            # returns False
rx.exactMatch("readme.txt")             # returns False
//! [12]


//! [13]
txt = QString("offsets: 1.23 .50 71.00 6.00")
rx = QRegExp("\\d*\\.\\d+")             # primitive floating point matching
count = 0
pos = rx.indexIn(txt, 0)
while pos != -1:
    count += 1
    pos += rx.matchedLength()
    pos = rx.indexIn(txt, pos)

# pos will be 9, 14, 18 and finally 24; count will end up as 4
//! [13]


//! [14]
rx = QRegExp("(\\d+)(\\s*)(cm|inch(es)?)")
pos = rx.indexIn("Length: 36 inches")
lst = rx.capturedTexts()
# lst is now ("36 inches", "36", " ", "inches", "es")
//! [14]


//! [15]
rx = QRegExp("(\\d+)(?:\\s*)(cm|inch(?:es)?)")
pos = rx.indexIn("Length: 36 inches")
lst = rx.capturedTexts()
# lst is now ("36 inches", "36", "inches")
//! [15]


//! [16]
for a in rx.capturedTexts():
    myProcessing(a)
//! [16]


//! [17]
rxlen  = QRegExp("(\\d+)(?:\\s*)(cm|inch)")
pos = rxlen.indexIn("Length: 189cm")
if pos > -1:
    value = rxlen.cap(1) # "189"
    unit = rxlen.cap(2)  # "cm"
//! [17]


//! [18]
rx = QRegExp("/([a-z]+)/([a-z]+)")
rx.indexIn("Output /dev/null")  # returns 7 (position of /dev/null)
rx.pos(0)                       # returns 7 (position of /dev/null)
rx.pos(1)                       # returns 8 (position of dev)
rx.pos(2)                       # returns 12 (position of null)
//! [18]


//! [19]
s1 = QRegExp.escape("bingo")    # s1 == "bingo"
s2 = QRegExp.escape("f(x)")     # s2 == "f\\(x\\)"
//! [19]


//! [20]
rx = QRegExp("(" + QRegExp.escape(name) + "|" + QRegExp.escape(alias) + ")")
//! [20]

