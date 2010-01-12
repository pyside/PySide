static void registerDynSignalSlot(QObject* source, const char* signature, QMetaMethod::MethodType type)
{
    const QMetaObject* metaObject = source->metaObject();
    int methodIndex = metaObject->indexOfMethod(signature);
    // Create the dynamic signal is needed
    if (methodIndex == -1) {
        SbkBaseWrapper* self = (SbkBaseWrapper*) BindingManager::instance().retrieveWrapper(source);
        if (!self->containsCppWrapper) {
            qWarning() << "You can't add dynamic signals or slots on an object originated from C++.";
        } else {
            PySide::DynamicQMetaObject* dynMetaObj = reinterpret_cast<PySide::DynamicQMetaObject*>(const_cast<QMetaObject*>(metaObject));
            if (type == QMetaMethod::Signal)
                dynMetaObj->addSignal(signature);
            else
                dynMetaObj->addSlot(signature);
        }
    }
}

static bool qobjectConnect(QObject* source, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    registerDynSignalSlot(source, signal, QMetaMethod::Signal);

    bool isSignal = PySide::isSignal(slot);
    slot++;
    registerDynSignalSlot(receiver, slot, isSignal ? QMetaMethod::Signal : QMetaMethod::Slot);
    return QObject::connect(source, signal - 1, receiver, slot - 1, type);
}

static bool qobjectConnectCallback(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType type)
{
    if (!PySide::checkSignal(signal))
        return false;
    signal++;

    registerDynSignalSlot(source, signal, QMetaMethod::Signal);
    int signalIndex = source->metaObject()->indexOfMethod(signal);

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

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::getCallbackSignature(signal, callback, usingGlobalReceiver).toAscii();
    const char* slot = callbackSig.constData();
    int slotIndex = metaObject->indexOfSlot(slot);
    if (slotIndex == -1) {
        if (!usingGlobalReceiver and !((SbkBaseWrapper*)self)->containsCppWrapper) {
            qWarning() << "You can't add dynamic slots on an object originated from C++.";
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
    if (QMetaObject::connect(source, signalIndex, receiver, slotIndex, type)) {
        // FIXME: Need to cast to QObjectWrapper* and call the public version of connectNotify
        //        when avoiding the protected hack.
        #ifndef AVOID_PROTECTED_HACK
            source->connectNotify(signal);
        #else
            reinterpret_cast<QObjectWrapper*>(source)->connectNotify_protected(signal);
        #endif
        if (usingGlobalReceiver)
            signalManager.globalReceiverConnectNotify(slotIndex);

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
    bool usingGlobalReceiver;
    QObject* receiver = 0;
    PyObject* self;
    if (PyMethod_Check(callback)) {
        self = PyMethod_GET_SELF(callback);
        if (SbkQObject_Check(self))
            receiver = SbkQObject_cptr(self);
    }
    usingGlobalReceiver = !receiver;
    if (usingGlobalReceiver)
        receiver = signalManager.globalReceiver();

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::getCallbackSignature(signal, callback, usingGlobalReceiver).toAscii();
    QByteArray qtSlotName(callbackSig);
    qtSlotName = qtSlotName.prepend('1');

    if (QObject::disconnect(source, signal, receiver, qtSlotName.constData())) {
        if (usingGlobalReceiver) {
            int slotIndex = metaObject->indexOfSlot(callbackSig.constData());
            signalManager.globalReceiverDisconnectNotify(slotIndex);
        }
        return true;
    }
    return false;
}
