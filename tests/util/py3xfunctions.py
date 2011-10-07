def b(s):
    if type(s) == bytes:
        return s
    return bytes(s, "UTF8")

def buffer_(s):
    if s == None:
        return None
    elif type(s) == str:
        return bytes(s, "UTF8")
    elif type(s) == bytes:
        return s
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
