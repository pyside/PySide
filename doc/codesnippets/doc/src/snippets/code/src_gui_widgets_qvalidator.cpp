//! [0]
validator = QIntValidator(100, 999, self)
edit = QLineEdit(self)

# the edit lineedit will only accept integers between 100 and 999
edit.setValidator(validator)
//! [0]


//! [1]
pos = 0
v = QIntValidator(100, 900, self)

str = "1"
v.validate(str, pos)     # returns Intermediate
str = "012"
v.validate(str, pos)     # returns Intermediate

str = "123"
v.validate(str, pos)     # returns Acceptable
str = "678"
v.validate(str, pos)     # returns Acceptable

str = "999"
v.validate(str, pos)    # returns Intermediate

str = "1234"
v.validate(str, pos)     # returns Invalid
str = "-123"
v.validate(str, pos)     # returns Invalid
str = "abc"
v.validate(str, pos)     # returns Invalid
str = "12cm"
v.validate(str, pos)     # returns Invalid
//! [1]


//! [2]
pos = 0

s = "abc"
v.validate(s, pos)    # returns Invalid

s = "5"
v.validate(s, pos)    # returns Intermediate

s = "50"
v.validate(s, pos)    # returns Acceptable
//! [2]


//! [3]
# regexp: optional '-' followed by between 1 and 3 digits
rx = QRegExp("-?\\d{1,3}")
validator = QRegExpValidator(rx, self)

edit = QLineEdit(self)
edit.setValidator(validator)
//! [3]


//! [4]
# integers 1 to 9999
rx = QRegExp("[1-9]\\d{0,3}")
# the validator treats the regexp as "^[1-9]\\d{0,3}$"
v = QRegExpValidator(rx, 0)
pos = 0

s = "0"
v.validate(s, pos)    # returns Invalid
s = "12345"
v.validate(s, pos)    # returns Invalid
s = "1"
v.validate(s, pos)    # returns Acceptable

rx.setPattern("\\S+")            # one or more non-whitespace characters
v.setRegExp(rx)
s = "myfile.txt"
v.validate(s, pos) # Returns Acceptable
s = "my file.txt"
v.validate(s, pos) # Returns Invalid

# A, B or C followed by exactly five digits followed by W, X, Y or Z
rx.setPattern("[A-C]\\d{5}[W-Z]")
v.setRegExp(rx)
s = "a12345Z"
v.validate(s, pos)        # Returns Invalid
s = "A12345Z"
v.validate(s, pos)        # Returns Acceptable
s = "B12"
v.validate(s, pos)        # Returns Intermediate

# match most 'readme' files
rx.setPattern("read\\S?me(\.(txt|asc|1st))?")
rx.setCaseSensitive(false)
v.setRegExp(rx)
s = "readme"
v.validate(s, pos) # Returns Acceptable
s = "README.1ST"
v.validate(s, pos) # Returns Acceptable
s = "read me.txt"
v.validate(s, pos) # Returns Invalid
s = "readm"
v.validate(s, pos) # Returns Intermediate
//! [4]
