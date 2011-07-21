static bool isDecorator(PyObject* method, PyObject* self)
{
    Shiboken::AutoDecRef methodName(PyObject_GetAttrString(method, "__name__"));
    if (!PyObject_HasAttr(self, methodName))
        return true;
    Shiboken::AutoDecRef otherMethod(PyObject_GetAttr(self, methodName));
    return reinterpret_cast<PyMethodObject*>(otherMethod.object())->im_func != \
           reinterpret_cast<PyMethodObject*>(method)->im_func;
}

static bool getReceiver(PyObject* callback, QObject** receiver, PyObject** self)
{
    bool forceGlobalReceiver = false;
    if (PyMethod_Check(callback)) {
        *self = PyMethod_GET_SELF(callback);
        if (Shiboken::Converter<QObject*>::checkType(*self))
            *receiver = Shiboken::Converter<QObject*>::toCpp(*self);
        forceGlobalReceiver = isDecorator(callback, *self);
    } else if (PyCFunction_Check(callback)) {
        *self = PyCFunction_GET_SELF(callback);
        if (*self && Shiboken::Converter<QObject*>::checkType(*self))
            *receiver = Shiboken::Converter<QObject*>::toCpp(*self);
    } else if (PyCallable_Check(callback)) {
        // Ok, just a callable object
        *receiver = 0;
        *self = 0;
    }

    bool usingGlobalReceiver = !*receiver || forceGlobalReceiver;
    if (usingGlobalReceiver) {
        PySide::SignalManager& signalManager = PySide::SignalManager::instance();
        *receiver = signalManager.globalReceiver();
    }

    return usingGlobalReceiver;
}

static bool qobjectConnect(QObject* source, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    if (!signal || !slot)
        return false;

    if (!PySide::Signal::checkQtSignal(signal))
        return false;
    signal++;

    if (!PySide::SignalManager::registerMetaMethod(source, signal, QMetaMethod::Signal))
        return false;

    bool isSignal = PySide::Signal::isQtSignal(slot);
    slot++;
    PySide::SignalManager::registerMetaMethod(receiver, slot, isSignal ? QMetaMethod::Signal : QMetaMethod::Slot);
    return QObject::connect(source, signal - 1, receiver, slot - 1, type);
}

static bool qobjectConnectCallback(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType type)
{
    if (!signal || !PySide::Signal::checkQtSignal(signal))
        return false;
    signal++;

    int signalIndex = PySide::SignalManager::registerMetaMethodGetIndex(source, signal, QMetaMethod::Signal);
    if (signalIndex == -1)
        return false;

    PySide::SignalManager& signalManager = PySide::SignalManager::instance();

    // Extract receiver from callback
    QObject* receiver = 0;
    PyObject* self = 0;
    bool usingGlobalReceiver = getReceiver(callback, &receiver, &self);
    if (receiver == 0 && self == 0)
        return false;

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::Signal::getCallbackSignature(signal, receiver, callback, usingGlobalReceiver).toAscii();
    const char* slot = callbackSig.constData();
    int slotIndex = metaObject->indexOfSlot(slot);
    if (slotIndex == -1) {
        if (!usingGlobalReceiver && self && !Shiboken::Object::hasCppWrapper((SbkObject*)self)) {
            qWarning() << "You can't add dynamic slots on an object originated from C++.";
            return false;
        }

        if (usingGlobalReceiver)
            slotIndex = signalManager.addGlobalSlotGetIndex(slot, callback);
        else
            slotIndex = PySide::SignalManager::registerMetaMethodGetIndex(receiver, slot, QMetaMethod::Slot);

        if (slotIndex == -1)
            return false;
    }
    if (QMetaObject::connect(source, signalIndex, receiver, slotIndex, type)) {
        if (usingGlobalReceiver)
            signalManager.globalReceiverConnectNotify(source, slotIndex);
        #ifndef AVOID_PROTECTED_HACK
            source->connectNotify(signal - 1);
        #else
            // Need to cast to QObjectWrapper* and call the public version of
            // connectNotify when avoiding the protected hack.
            reinterpret_cast<QObjectWrapper*>(source)->connectNotify(signal - 1);
        #endif

        return true;
    }
    return false;
}


static bool qobjectDisconnectCallback(QObject* source, const char* signal, PyObject* callback)
{
    if (!PySide::Signal::checkQtSignal(signal))
        return false;

    PySide::SignalManager& signalManager = PySide::SignalManager::instance();

    // Extract receiver from callback
    QObject* receiver = 0;
    PyObject* self = 0;
    bool usingGlobalReceiver = getReceiver(callback, &receiver, &self);
    if (receiver == 0 && self == 0)
        return false;

    const QMetaObject* metaObject = receiver->metaObject();
    const QByteArray callbackSig = PySide::Signal::getCallbackSignature(signal, receiver, callback, usingGlobalReceiver).toAscii();
    QByteArray qtSlotName(callbackSig);
    qtSlotName = qtSlotName.prepend('1');

    if (QObject::disconnect(source, signal, receiver, qtSlotName.constData())) {
        if (usingGlobalReceiver) {
            int slotIndex = metaObject->indexOfSlot(callbackSig.constData());
            signalManager.globalReceiverDisconnectNotify(source, slotIndex);
        #ifndef AVOID_PROTECTED_HACK
            source->disconnectNotify(signal - 1);
        #else
            // Need to cast to QObjectWrapper* and call the public version of
            // connectNotify when avoiding the protected hack.
            reinterpret_cast<QObjectWrapper*>(source)->disconnectNotify(signal - 1);
        #endif
        }
        return true;
    }
    return false;
}
