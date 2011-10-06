def b(s):
    return s

def l(n):
    return long(n)

def unicode_(s):
    if type(s) == str:
        import codecs
        c = codecs.lookup('utf-8')
        s2 = c.decode(s, 'ignore')
        return s2[0]
    return u'%s' % s

unicode = unicode
unichr = unichr
long = long
buffer = buffer
