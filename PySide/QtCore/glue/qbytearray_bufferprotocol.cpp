
#if PY_VERSION_HEX < 0x03000000

// QByteArray buffer protocol functions
// see: http://www.python.org/dev/peps/pep-3118/

extern "C" {

static Py_ssize_t SbkQByteArray_segcountproc(PyObject* self, Py_ssize_t* lenp)
{
    if (lenp)
        *lenp = self->ob_type->tp_as_sequence->sq_length(self);
    return 1;
}

static Py_ssize_t SbkQByteArray_readbufferproc(PyObject* self, Py_ssize_t segment, void** ptrptr)
{
    if (segment || !Shiboken::Object::isValid(self))
        return -1;

    QByteArray* cppSelf = %CONVERTTOCPP[QByteArray*](self);
    *ptrptr = reinterpret_cast<void*>(cppSelf->data());
    return cppSelf->size();
}

PyBufferProcs SbkQByteArrayBufferProc = {
    /*bf_getreadbuffer*/  &SbkQByteArray_readbufferproc,
    /*bf_getwritebuffer*/ (writebufferproc) &SbkQByteArray_readbufferproc,
    /*bf_getsegcount*/    &SbkQByteArray_segcountproc,
    /*bf_getcharbuffer*/  (charbufferproc) &SbkQByteArray_readbufferproc
};

}

#endif
