
#if PY_VERSION_HEX < 0x03000000

// QByteArray buffer protocol functions
// see: http://www.python.org/dev/peps/pep-3118/

extern "C" {

static Py_ssize_t SbkQString_segcountproc(PyObject* self, Py_ssize_t* lenp)
{
    if (lenp)
        *lenp = self->ob_type->tp_as_sequence->sq_length(self);
    return 1;
}

static Py_ssize_t SbkQString_readbufferproc(PyObject* self, Py_ssize_t segment, char** ptrptr)
{
    if (segment || Shiboken::cppObjectIsInvalid(self))
        return -1;

    QString* cppSelf = SbkQString_cptr(self);
    QByteArray decodedData = cppSelf->toLocal8Bit();
    Shiboken::AutoDecRef decodedString(PyString_FromStringAndSize(decodedData.constData(), decodedData.size()));

    // delete __encodedStr attr if it exists
    Shiboken::AutoDecRef attrName(PyString_FromStringAndSize("__encodedStr", sizeof("__encodedStr")-1));
    if (PyObject_HasAttr(self, attrName))
        PyObject_DelAttr(self, attrName);
    PyObject_SetAttr(self, attrName, decodedString);
    *ptrptr = PyString_AS_STRING(decodedString.object());
    return decodedData.size();
}

PyBufferProcs SbkQStringBufferProc = {
    /*bf_getreadbuffer*/  0,
    /*bf_getwritebuffer*/ 0,
    /*bf_getsegcount*/    &SbkQString_segcountproc,
    /*bf_getcharbuffer*/  &SbkQString_readbufferproc
};

}

#endif
