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

static void _findChildrenHelper(const QObject* parent, const QString& name, PyTypeObject* desiredType, PyObject* result)
{
    foreach(QObject* child, parent->children()) {
        Shiboken::AutoDecRef pyChild(%CONVERTTOPYTHON[QObject*](child));
        if (PyType_IsSubtype(pyChild->ob_type, desiredType)
            && (name.isNull() || name == child->objectName())) {
            PyList_Append(result, pyChild);
        }
        _findChildrenHelper(child, name, desiredType, result);
    }
}