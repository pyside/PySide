inline bool Converter< QString >::isConvertible(PyObject* pyobj)
{
    return PyString_Check(pyobj)
            || PyUnicode_Check(pyobj)
            || SbkQByteArray_Check(pyobj)
            || SbkQLatin1String_Check(pyobj)
#if PY_VERSION_HEX < 0x03000000
            || (pyobj->ob_type->tp_as_buffer
               && PyType_HasFeature(pyobj->ob_type, Py_TPFLAGS_HAVE_GETCHARBUFFER)
               && pyobj->ob_type->tp_as_buffer->bf_getcharbuffer)
#endif
            || SbkQChar_Check(pyobj);
}

inline QString Converter< QString >::toCpp(PyObject* pyobj)
{
    if (SbkQChar_Check(pyobj)) {
        return QString(Converter< QChar >::toCpp(pyobj));
    } else if (SbkQByteArray_Check(pyobj)) {
        return QString(Converter< QByteArray >::toCpp(pyobj));
    } else if (SbkQLatin1String_Check(pyobj)) {
        return QString(Converter< QLatin1String >::toCpp(pyobj));
    } else if (PyUnicode_Check(pyobj)) {
        Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyobj);
#if defined(Py_UNICODE_WIDE)
        return QString::fromUcs4(unicode);
#else
        return QString::fromUtf16(unicode, PyUnicode_GET_SIZE(pyobj));
#endif
    } else if (PyString_Check(pyobj)) {
        return QString(Converter< char * >::toCpp(pyobj));
    }
#if PY_VERSION_HEX < 0x03000000
    // Support for buffer objects on QString constructor
    else if (pyobj->ob_type->tp_as_buffer
               && PyType_HasFeature(pyobj->ob_type, Py_TPFLAGS_HAVE_GETCHARBUFFER)
               && pyobj->ob_type->tp_as_buffer->bf_getcharbuffer) {
        QByteArray data;
        PyBufferProcs* bufferProcs = pyobj->ob_type->tp_as_buffer;
        int segments = bufferProcs->bf_getsegcount(pyobj, 0);
        for (int i = 0; i < segments; ++i) {
            char* segmentData;
            int length = bufferProcs->bf_getcharbuffer(pyobj, i, &segmentData);
            if (length == -1)
                break;
            data.append(segmentData, length);
        }
        return QString(data);
    }
#endif
    return *SbkQString_cptr(pyobj);
}
