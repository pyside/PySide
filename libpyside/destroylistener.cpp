#include <Python.h>
#include "destroylistener.h"

#include <QObject>
#include <shiboken.h>
#include <QDebug>
#include <QMutex>

PySide::DestroyListener* PySide::DestroyListener::m_instance = 0;

namespace PySide
{

struct DestroyListenerPrivate
{
    static bool m_destroyed;
};


DestroyListener* DestroyListener::instance()
{
    if (!m_instance)
        m_instance = new DestroyListener(0);
    return m_instance;
}

void DestroyListener::destroy()
{
    if (m_instance) {
        m_instance->disconnect();
        delete m_instance;
        m_instance = 0;
    }
}

void DestroyListener::listen(QObject *obj)
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(obj);
    if (!wrapper) // avoid problem with multiple inheritance
        return;

    if (Py_IsInitialized() == 0)
        onObjectDestroyed(obj);
    else
        QObject::connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(onObjectDestroyed(QObject*)), Qt::DirectConnection);
}

void DestroyListener::onObjectDestroyed(QObject* obj)
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(obj);
    if (wrapper) //make sure the object exists before destroy
        Shiboken::Object::destroy(wrapper, obj);
}

DestroyListener::DestroyListener(QObject *parent)
    : QObject(parent)
{
    m_d = new DestroyListenerPrivate();
}

DestroyListener::~DestroyListener()
{
    delete m_d;
}

}//namespace

