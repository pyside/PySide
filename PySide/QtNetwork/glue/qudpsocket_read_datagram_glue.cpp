    char data[%ARGUMENT_NAMES];
    QHostAddress ha;
    quint16 port;

    %RETURN_TYPE retval = %CPPSELF.%FUNCTION_NAME(data, %ARGUMENT_NAMES, &ha, &port);
    %PYARG_0 = Shiboken::makeTuple(QByteArray(data, retval), ha, port);
