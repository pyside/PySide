namespace Shiboken {

template<>
inline PyTypeObject* SbkType<QString>()
{
    return &PyUnicode_Type;
}

template<>
struct Converter<QString>
{
    static bool checkType(PyObject* pyObj)
    {
        return PyString_Check(pyObj) || PyUnicode_Check(pyObj);
    }

    static bool isConvertible(PyObject* pyObj)
    {
        return PyString_Check(pyObj)
                || PyUnicode_Check(pyObj)
                || SbkQByteArray_Check(pyObj)
                || pyObj == Py_None
    #if PY_VERSION_HEX < 0x03000000
                || (pyObj->ob_type->tp_as_buffer
                && PyType_HasFeature(pyObj->ob_type, Py_TPFLAGS_HAVE_GETCHARBUFFER)
                && pyObj->ob_type->tp_as_buffer->bf_getcharbuffer)
    #endif
                ;
    }

    static QString toCpp(PyObject* pyObj)
    {
        if (PyUnicode_Check(pyObj)) {
            Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyObj);
    #if defined(Py_UNICODE_WIDE)
            // cast as Py_UNICODE can be a different type
            return QString::fromUcs4(reinterpret_cast<const uint*>(unicode));
    #else
            return QString::fromUtf16(unicode, PyUnicode_GET_SIZE(pyObj));
    #endif
        } else if (PyString_Check(pyObj)) {
            return QString(Converter< char * >::toCpp(pyObj));
        } else if (pyObj == Py_None) {
            return QString();
        } else if (SbkQByteArray_Check(pyObj)) {
            return QString(Converter< QByteArray >::toCpp(pyObj));
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
        return QString();
    }

    static PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QString*>(cppObj)); }
    static PyObject* toPython(const QString& cppObj)
    {
        const int N = cppObj.length();
        wchar_t* str = new wchar_t[N];
        cppObj.toWCharArray(str);
        PyObject* pyObj = PyUnicode_FromWideChar(str, N);
        delete[] str;
        return pyObj;
    }
};
}
