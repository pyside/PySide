static int qobjectGetMethodIndex(QObject* source, const char* signature, QMetaMethod::MethodType type)
{
    const QMetaObject* metaObject = source->metaObject();
    int methodIndex = metaObject->indexOfMethod(signature);
    // Create the dynamic signal is needed
    if (methodIndex == -1) {
        SbkBaseWrapper* self = (SbkBaseWrapper*) BindingManager::instance().retrieveWrapper(source);
        if (!self->containsCppWrapper) {
            qWarning() << "You can't add dynamic signals or slots on an object originated from C++.";
            return false;
        }
        PySide::DynamicQMetaObject* dynMetaObj = reinterpret_cast<PySide::DynamicQMetaObject*>(const_cast<QMetaObject*>(metaObject));
        if (type == QMetaMethod::Signal)
            dynMetaObj->addSignal(signature);
        else
            dynMetaObj->addSlot(signature);
        methodIndex = metaObject->indexOfMethod(signature);
    }
    return methodIndex;
}

static bool qobjectConnect(QObject* source, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    const QMetaObject* metaObject = source->metaObject();
    int signalIndex = qobjectGetMethodIndex(source, signal, QMetaMethod::Signal);

    bool isSignal = PySide::isSignal(slot);
    slot++;
    metaObject = receiver->metaObject();
    int slotIndex = qobjectGetMethodIndex(receiver, slot, isSignal ? QMetaMethod::Signal : QMetaMethod::Slot);
    return QMetaObject::connect(source, signalIndex, receiver, slotIndex, type);
}

static bool qobjectConnectCallback(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    const QMetaObject* metaObject = source->metaObject();
    int signalIndex = qobjectGetMethodIndex(source, signal, QMetaMethod::Signal);

    PySide::SignalManager& signalManager = PySide::SignalManager::instance();

    // Extract receiver from callback
    bool usingGlobalReceiver;
    QObject* receiver = 0;
    PyObject* self;
    if (PyMethod_Check(callback)) {
        self = PyMethod_GET_SELF(callback);
        if (SbkQObject_Check(self))
            receiver = SbkQObject_cptr(self);
    } else if (PyCFunction_Check(callback)) {
        self = PyCFunction_GET_SELF(callback);
        if (self && SbkQObject_Check(self))
            receiver = SbkQObject_cptr(self);
    }
    usingGlobalReceiver = !receiver;
    if (usingGlobalReceiver)
        receiver = signalManager.globalReceiver();

    metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::getCallbackSignature(signal, callback, usingGlobalReceiver).toAscii();
    const char* slot = callbackSig.constData();
    int slotIndex = metaObject->indexOfSlot(slot);
    if (slotIndex == -1) {
        if (!usingGlobalReceiver and !((SbkBaseWrapper*)self)->containsCppWrapper) {
            qWarning() << "You cant add dynamic slots on an object originated from C++.";
            return false;
        }
        if (usingGlobalReceiver) {
            signalManager.addGlobalSlot(slot, callback);
        } else {
            PySide::DynamicQMetaObject* dynMetaObj = reinterpret_cast<PySide::DynamicQMetaObject*>(const_cast<QMetaObject*>(metaObject));
            dynMetaObj->addSlot(slot);
        }
        slotIndex = metaObject->indexOfSlot(slot);
    }
    return QMetaObject::connect(source, signalIndex, receiver, slotIndex, type);
}
