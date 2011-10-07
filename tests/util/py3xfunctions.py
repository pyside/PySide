def b(s):
    return bytes(s, "UTF8")

def buffer_(s):
    if s == None:
        return None
    elif type(s) == str:
        return bytes(s, "UTF8")
    else:
        memoryview(s)

def l(n):
    return n

def unicode_(s):
    return s

unicode = str
unichr = chr
long = int
unichr = chr
buffer = buffer_
