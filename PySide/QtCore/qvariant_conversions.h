namespace Shiboken {

template<>
struct Converter<QVariant>
{
    static bool checkType(PyObject* pyObj)
    {
        return false; // lets avoid the chaos
    }

    // all types are convertible to QVariant
    static bool isConvertible(PyObject* pyObj)
    {
        return true;
    }

    static QVariant toCpp(PyObject* pyObj)
    {
        using namespace Shiboken;

        // Primitive types
        if (Converter<bool>::checkType(pyObj)) {
            // QVariant(bool)
            return QVariant(Converter<bool>::toCpp(pyObj));
        } else if (pyObj == Py_None) {
            // QVariant()
            return QVariant();
        } else if (Converter<QString>::checkType(pyObj)) {
            // QVariant(const char*)
            return QVariant(Converter<QString>::toCpp(pyObj));
        } else if (Converter<QByteArray>::checkType(pyObj)) {
            // QVariant(QByteArray)
            return QVariant(Converter<QByteArray>::toCpp(pyObj));
        } else if (PyFloat_CheckExact(pyObj)) {
            // QVariant(double)
            return QVariant(Converter<double>::toCpp(pyObj));
        } else if (PyInt_Check(pyObj)) {
            // QVariant(int)
            return QVariant(Converter<int>::toCpp(pyObj));
        } else if (PyLong_CheckExact(pyObj)) {
            // QVariant(qlonglong)
            return QVariant(Converter<qlonglong>::toCpp(pyObj));
        } else if (Shiboken::isShibokenEnum(pyObj)) {
            // QVariant(enum)
            return QVariant(Converter<int>::toCpp(pyObj));
        } else if (PyDict_Check(pyObj)) {
            return convertToVariantMap(pyObj);
        } else if (PySequence_Check(pyObj)) {
            return convertToVariantList(pyObj);
        } else if (!isShibokenType(pyObj) || isUserType(pyObj)) {
            // QVariant(User class)
            return QVariant::fromValue<PySide::PyObjectWrapper>(pyObj);
        } else {
            // a class supported by QVariant?
            if (Shiboken::isShibokenType(pyObj)) {
                Shiboken::SbkBaseWrapperType *objType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(pyObj->ob_type);
                const char* typeName = objType->original_name;
                uint typeCode = QMetaType::type(typeName);
                if (!typeCode) {// Try with star at end, for QObject*, QWidget* and QAbstractKinectScroller*
                    QString stypeName(typeName);
                    stypeName += '*';
                    typeCode = QMetaType::type(stypeName.toAscii());
                    return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyObj)->cptr);
                }
                if (typeCode)
                    return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyObj)->cptr[0]);
            }
            // Is a shiboken type not known by Qt
            return QVariant::fromValue<PySide::PyObjectWrapper>(pyObj);
        }
    }

    static PyObject* toPython(void* cppObj)
    {
        return toPython(*reinterpret_cast<QVariant*>(cppObj));
    }

    static PyObject* toPython(const QVariant& cppObj)
    {
        if (cppObj.isValid()) {
            if (qstrcmp(cppObj.typeName(), "QVariantList") == 0)
                return Converter<QList<QVariant> >::toPython(cppObj.value<QVariantList>());

            if (qstrcmp(cppObj.typeName(), "QStringList") == 0)
                return Converter<QList<QString> >::toPython(cppObj.value<QStringList>());

            if (qstrcmp(cppObj.typeName(), "QVariantMap") == 0)
                return Converter<QMap<QString, QVariant> >::toPython(cppObj.value<QVariantMap>());

            Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(cppObj.typeName());
            if (tr)
                return tr->toPython(const_cast<void*>(cppObj.data()));
        }
        Py_RETURN_NONE;
    }

    static QVariant convertToVariantMap(PyObject* map)
    {
        PyObject *key, *value;
        Py_ssize_t pos = 0;
        AutoDecRef keys(PyDict_Keys(map));
        bool keysIsString = isStringList(keys);
        if (keysIsString) {
            QMap<QString, QVariant> ret;
            while (PyDict_Next(map, &pos, &key, &value))
                ret.insert(Converter<QString>::toCpp(key), toCpp(value));
            return QVariant(ret);
        } else {
            return toCpp(map);
        }
    }

    static bool isStringList(PyObject *list)
    {
        bool allString = true;
        AutoDecRef fast(PySequence_Fast(list, "Failed to convert QVariantList"));
        Py_ssize_t size = PySequence_Fast_GET_SIZE(fast.object());
        for(int i=0; i < size; i++) {
            PyObject* item = PySequence_Fast_GET_ITEM(fast.object(), i);
            if (!Converter<QString>::checkType(item)) {
                allString = false;
                break;
            }
        }
        return allString;
    }

    static QVariant convertToVariantList(PyObject* list)
    {
        bool allString = isStringList(list);
        if (allString) {
            QStringList lst = Converter<QList<QString> >::toCpp(list);
            return QVariant(lst);
        } else {
            QList<QVariant> lst;
            AutoDecRef fast(PySequence_Fast(list, "Failed to convert QVariantList"));
            Py_ssize_t size = PySequence_Fast_GET_SIZE(fast.object());
            for(int i=0; i < size; i++) {
                PyObject* item = PySequence_Fast_GET_ITEM(fast.object(), i);
                lst.append(toCpp(item));
            }
            return QVariant(lst);
        }
        Q_ASSERT(false);
    }
};
}
