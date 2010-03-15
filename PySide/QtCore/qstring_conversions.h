namespace Shiboken {
inline bool Converter<QString>::isConvertible(PyObject* pyObj)
{
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QString>());
    return PyString_Check(pyObj)
            || PyObject_TypeCheck(pyObj, SbkType<QString>())
            || PyUnicode_Check(pyObj)
            || SbkQByteArray_Check(pyObj)
            || SbkQLatin1String_Check(pyObj)
#if PY_VERSION_HEX < 0x03000000
            || (pyObj->ob_type->tp_as_buffer
               && PyType_HasFeature(pyObj->ob_type, Py_TPFLAGS_HAVE_GETCHARBUFFER)
               && pyObj->ob_type->tp_as_buffer->bf_getcharbuffer)
#endif
            || SbkQChar_Check(pyObj)
            || (shiboType->ext_isconvertible && shiboType->ext_isconvertible(pyObj));
}

inline QString Converter<QString>::toCpp(PyObject* pyObj)
{
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QString>());
    if (SbkQChar_Check(pyObj)) {
        return QString(Converter< QChar >::toCpp(pyObj));
    } else if (SbkQByteArray_Check(pyObj)) {
        return QString(Converter< QByteArray >::toCpp(pyObj));
    } else if (SbkQLatin1String_Check(pyObj)) {
        return QString(Converter< QLatin1String >::toCpp(pyObj));
    } else if (PyUnicode_Check(pyObj)) {
        Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyObj);
#if defined(Py_UNICODE_WIDE)
        // cast as Py_UNICODE can be a different type
        return QString::fromUcs4(reinterpret_cast<const uint*>(unicode));
#else
        return QString::fromUtf16(unicode, PyUnicode_GET_SIZE(pyObj));
#endif
    } else if (PyString_Check(pyObj)) {
        return QString(Converter< char * >::toCpp(pyObj));
    }
#if PY_VERSION_HEX < 0x03000000
    // Support for buffer objects on QString constructor
    else if (pyObj->ob_type->tp_as_buffer
               && PyType_HasFeature(pyObj->ob_type, Py_TPFLAGS_HAVE_GETCHARBUFFER)
               && pyObj->ob_type->tp_as_buffer->bf_getcharbuffer) {
        QByteArray data;
        PyBufferProcs* bufferProcs = pyObj->ob_type->tp_as_buffer;
        int segments = bufferProcs->bf_getsegcount(pyObj, 0);
        for (int i = 0; i < segments; ++i) {
            char* segmentData;
            int length = bufferProcs->bf_getcharbuffer(pyObj, i, &segmentData);
            if (length == -1)
                break;
            data.append(segmentData, length);
        }
        return QString(data);
    }
#endif
    else if (shiboType->ext_isconvertible && shiboType->ext_tocpp && shiboType->ext_isconvertible(pyObj)) {
        QString* cptr = reinterpret_cast<QString*>(shiboType->ext_tocpp(pyObj));
        std::auto_ptr<QString> cptr_auto_ptr(cptr);
        return *cptr;
    }
    return *Converter<QString*>::toCpp(pyObj);
}

inline PyObject* Converter<QString>::toPython(const QString& cppObj)
{
    return ValueTypeConverter<QString>::toPython(cppObj);
}
}
