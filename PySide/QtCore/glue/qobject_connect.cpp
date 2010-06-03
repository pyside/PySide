static bool getReceiver(PyObject *callback, QObject **receiver, PyObject **self)
{
    if (PyMethod_Check(callback)) {
        *self = PyMethod_GET_SELF(callback);
        if (SbkQObject_Check(*self))
            *receiver = Converter<QObject*>::toCpp(*self);
    } else if (PyCFunction_Check(callback)) {
        *self = PyCFunction_GET_SELF(callback);
        if (*self && SbkQObject_Check(*self))
            *receiver = Converter<QObject*>::toCpp(*self);
    } else if (PyCallable_Check(callback)) {
        // Ok, just a callable object
        *receiver = 0;
        *self = 0;
    }

    bool usingGlobalReceiver = !*receiver;
    if (usingGlobalReceiver) {
        PySide::SignalManager& signalManager = PySide::SignalManager::instance();
        *receiver = signalManager.globalReceiver();
    }

    return usingGlobalReceiver;
}

static bool qobjectConnect(QObject* source, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    PySide::SignalManager::registerMetaMethod(source, signal, QMetaMethod::Signal);

    bool isSignal = PySide::isSignal(slot);
    slot++;
    PySide::SignalManager::registerMetaMethod(receiver, slot, isSignal ? QMetaMethod::Signal : QMetaMethod::Slot);
    return QObject::connect(source, signal - 1, receiver, slot - 1, type);
}

static bool qobjectConnectCallback(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    PySide::SignalManager::registerMetaMethod(source, signal, QMetaMethod::Signal);
    int signalIndex = source->metaObject()->indexOfMethod(signal);

    PySide::SignalManager& signalManager = PySide::SignalManager::instance();

    // Extract receiver from callback
    QObject* receiver = 0;
    PyObject* self = 0;
    bool usingGlobalReceiver = getReceiver(callback, &receiver, &self);
    if (receiver == 0 && self == 0)
        return false;

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::getCallbackSignature(signal, callback, usingGlobalReceiver).toAscii();
    const char* slot = callbackSig.constData();
    int slotIndex = metaObject->indexOfSlot(slot);
    if (slotIndex == -1) {
        if (!usingGlobalReceiver && self && !((SbkBaseWrapper*)self)->containsCppWrapper) {
            qWarning() << "You can't add dynamic slots on an object originated from C++.";
            return false;
        }
        if (usingGlobalReceiver) {
            signalManager.addGlobalSlot(slot, callback);
        } else {
            PySide::SignalManager::registerMetaMethod(receiver, slot, QMetaMethod::Slot);
        }
        slotIndex = metaObject->indexOfSlot(slot);
    }
    if (QMetaObject::connect(source, signalIndex, receiver, slotIndex, type)) {
        #ifndef AVOID_PROTECTED_HACK
            source->connectNotify(signal);
        #else
            // Need to cast to QObjectWrapper* and call the public version of
            // connectNotify when avoiding the protected hack.
            reinterpret_cast<QObjectWrapper*>(source)->connectNotify(signal);
        #endif
        if (usingGlobalReceiver)
            signalManager.globalReceiverConnectNotify(source, slotIndex);

        return true;
    }
    return false;
}


static bool qobjectDisconnectCallback(QObject* source, const char* signal, PyObject* callback)
{
    if (!PySide::checkSignal(signal))
        return false;

    PySide::SignalManager& signalManager = PySide::SignalManager::instance();

    // Extract receiver from callback
    QObject* receiver = 0;
    PyObject* self = 0;
    bool usingGlobalReceiver = getReceiver(callback, &receiver, &self);
    if (receiver == 0 && self == 0)
        return false;

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::getCallbackSignature(signal, callback, usingGlobalReceiver).toAscii();
    QByteArray qtSlotName(callbackSig);
    qtSlotName = qtSlotName.prepend('1');

    if (QObject::disconnect(source, signal, receiver, qtSlotName.constData())) {
        if (usingGlobalReceiver) {
            int slotIndex = metaObject->indexOfSlot(callbackSig.constData());
            signalManager.globalReceiverDisconnectNotify(source, slotIndex);
        }
        return true;
    }
    return false;
}
