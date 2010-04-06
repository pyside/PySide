static long QStringCustomHashFunction(const QString& str)
{
    QByteArray data = str.toUtf8();
    Shiboken::AutoDecRef unicodeObj(PyUnicode_DecodeUTF8(data.constData(), data.length(), 0));
    return unicodeObj->ob_type->tp_hash(unicodeObj);
}
