#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#ifdef pysidetest_EXPORTS
#define PYSIDE_EXPORTS 1
#endif
#include "pysidemacros.h"

class PYSIDE_API TestObject : public QObject
{
    Q_OBJECT
public:
    TestObject(int idValue, QObject* parent = 0) : QObject(parent), m_idValue(idValue) {}
    int idValue() const { return m_idValue; }
    static int staticMethodDouble(int value) { return value * 2; }

    void emitIdValueSignal();
    void emitStaticMethodDoubleSignal();

signals:
    void idValue(int newValue);
    void justASignal();
    void staticMethodDouble();

private:
    int m_idValue;
};

#endif // TESTOBJECT_H

