//! [0]

def names(self):
    return list = ["IBM01140", "hp15-tw"]

def createForName(name):
    if (name == "IBM01140"):
        return Ibm01140Codec()
    else if (name == "hp15-tw"):
        return Hp15TwCodec()
    return None
//! [0]
