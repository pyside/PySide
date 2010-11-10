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

    static QByteArray resolveMetaType(PyTypeObject* type, int &typeId)
    {
        if (PyObject_TypeCheck(type, &Shiboken::SbkBaseWrapperType_Type)) {
            Shiboken::SbkBaseWrapperType *sbkType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(type);
            QByteArray typeName(sbkType->original_name);
            bool valueType = !typeName.endsWith("*");

            // Do not convert user type of value
            if (valueType && sbkType->is_user_type)
                return QByteArray();

            int obTypeId = QMetaType::type(typeName);
            if (obTypeId) {
                typeId = obTypeId;
                return QByteArray(typeName);
            }

            // Do not resolve types to value type
            if (valueType)
                return QByteArray();

            // find in base types
            if (type->tp_base) {
                return resolveMetaType(type->tp_base, typeId);
            } else if (type->tp_bases) {
                int size = PyTuple_GET_SIZE(type->tp_bases);
                for(int i=0; i < size; i++){
                    QByteArray derivedName = resolveMetaType(reinterpret_cast<PyTypeObject*>(PyTuple_GET_ITEM(type->tp_bases, i)), typeId);
                    if (!derivedName.isEmpty())
                        return derivedName;
                }
            }
        }
        typeId = 0;
        return QByteArray();
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
        } else {
            // a class supported by QVariant?
            if (Shiboken::isShibokenType(pyObj)) {
                Shiboken::SbkBaseWrapperType *objType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(pyObj->ob_type);
                int typeCode = 0;
                QByteArray typeName = resolveMetaType(reinterpret_cast<PyTypeObject*>(objType), typeCode);
                if (typeCode) {
                    Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(typeName);
                    void* data = 0;
                    data = tr->toCpp(pyObj, &data, true);
                    if (typeName.endsWith("*")) {
                        QVariant var(typeCode, &data);
                        tr->deleteObject(data);
                        return var;
                    } else {
                        QVariant var(typeCode, data);
                        tr->deleteObject(data);
                        return var;
                    }
                }
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

    static QVariant convertToValueList(PyObject* list)
    {
        if (PySequence_Size(list) < 1)
            return QVariant();

        Shiboken::AutoDecRef element(PySequence_GetItem(list, 0));
        int typeId = 0;
        QByteArray typeName = resolveMetaType(element.cast<PyTypeObject*>(), typeId);
        if (!typeName.isEmpty()) {
            QByteArray listTypeName = QByteArray("QList<"+typeName+">");
            typeId = QMetaType::type(listTypeName);
            if (typeId > 0) {
                Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(listTypeName);
                if (!tr) {
                    qWarning() << "TypeResolver for :" << listTypeName << "not registered.";
                    return QVariant();
                } else {
                    void *data = 0;
                    data = tr->toCpp(list, &data, true);
                    QVariant var(typeId, data);
                    tr->deleteObject(data);
                    return var;
                }
            } else {
                return QVariant();
            }
        }

        return QVariant();
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
            QVariant valueList = convertToValueList(list);
            if (valueList.isValid())
                return valueList;
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
