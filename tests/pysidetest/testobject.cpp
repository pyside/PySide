#include "testobject.h"

void
TestObject::emitIdValueSignal()
{
    emit idValue(m_idValue);
}

void
TestObject::emitStaticMethodDoubleSignal()
{
    emit staticMethodDouble();
}

void
TestObject::emitSignalWithDefaultValue_void()
{
    emit signalWithDefaultValue();
}

void
TestObject::emitSignalWithDefaultValue_bool()
{
    emit signalWithDefaultValue(true);
}

