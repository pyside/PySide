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

