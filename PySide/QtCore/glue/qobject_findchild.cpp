static QObject* _findChildHelper(const QObject* parent, const QString& name, PyTypeObject* desiredType)
{
    foreach(QObject* child, parent->children()) {
        Shiboken::AutoDecRef pyChild(%CONVERTTOPYTHON[QObject*](child));
        if (PyType_IsSubtype(pyChild->ob_type, desiredType)
            && (name.isNull() || name == child->objectName())) {
            return child;
        }
    }

    QObject* obj;
    foreach(QObject* child, parent->children()) {
        obj = _findChildHelper(child, name, desiredType);
        if (obj)
            return obj;
    }
    return 0;
}

static inline bool _findChildrenComparator(const QObject*& child, const QRegExp& name)
{
    return name.indexIn(child->objectName()) != -1;
}

static inline bool _findChildrenComparator(const QObject*& child, const QString& name)
{
    return name.isNull() || name == child->objectName();
}

template<typename T>
static void _findChildrenHelper(const QObject* parent, const T& name, PyTypeObject* desiredType, PyObject* result)
{
    foreach(const QObject* child, parent->children()) {
        Shiboken::AutoDecRef pyChild(%CONVERTTOPYTHON[QObject*](child));
        if (PyType_IsSubtype(pyChild->ob_type, desiredType) && _findChildrenComparator(child, name))
            PyList_Append(result, pyChild);
        _findChildrenHelper(child, name, desiredType, result);
    }
}
