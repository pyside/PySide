#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include <QApplication>
#include <QMetaType>
#include <QVariant>
#ifdef pysidetest_EXPORTS
#define PYSIDE_EXPORTS 1
#endif
#include "pysidemacros.h"

class PYSIDE_API TestObject : public QObject
{
    Q_OBJECT
public:
    static void createApp() { int argc=0; new QApplication(argc, 0); };
    static int checkType(const QVariant& var) { return (int)var.type(); }

    TestObject(int idValue, QObject* parent = 0) : QObject(parent), m_idValue(idValue) {}
    int idValue() const { return m_idValue; }
    static int staticMethodDouble(int value) { return value * 2; }
    void addChild(QObject* c) { m_children.append(c); emit childrenChanged(m_children); }

    void emitIdValueSignal();
    void emitStaticMethodDoubleSignal();

    void emitSignalWithDefaultValue_void();
    void emitSignalWithDefaultValue_bool();

signals:
    void idValue(int newValue);
    void justASignal();
    void staticMethodDouble();
    void childrenChanged(const QList<QObject*>&);
    void signalWithDefaultValue(bool value = false);

private:
    int m_idValue;
    QList<QObject*> m_children;
};


typedef int PySideInt;


namespace PySideCPP {

class PYSIDE_API TestObjectWithNamespace :  public QObject
{
    Q_OBJECT
public:
    TestObjectWithNamespace(QObject* parent) : QObject(parent) {}
    QString name() { return "TestObjectWithNamespace"; }

    void callSignal(TestObjectWithNamespace* obj) { emitSignal(obj); }
    void callSignalWithNamespace(TestObjectWithNamespace* obj) { emitSignalWithNamespace(obj); }
    void callSignalWithTypedef(int val) { emitSignalWithTypedef(val); }

signals:
    void emitSignal(TestObjectWithNamespace* obj);
    void emitSignalWithNamespace(PySideCPP::TestObjectWithNamespace* obj);
    void emitSignalWithTypedef(PySideInt val);
};


} // Namespace PySideCPP

namespace PySideCPP2 {

enum Enum1 { Option1 = 1, Option2 = 2 };


typedef long PySideLong;

class PYSIDE_API TestObjectWithoutNamespace :  public QObject
{
    Q_OBJECT
public:
    enum Enum2 { Option3 = 3, Option4 =  4};
    TestObjectWithoutNamespace(QObject* parent) : QObject(parent) {}
    QString name() { return "TestObjectWithoutNamespace"; }

    void callSignal(TestObjectWithoutNamespace* obj) { emitSignal(obj); }
    void callSignalWithNamespace(TestObjectWithoutNamespace* obj) { emitSignalWithNamespace(obj); }
    void callSignalWithTypedef(long val) { emitSignalWithTypedef(val); }

signals:
    void emitSignal(TestObjectWithoutNamespace* obj);
    void emitSignalWithNamespace(PySideCPP2::TestObjectWithoutNamespace* obj);
    void emitSignalWithTypedef(PySideLong val);
};


} // Namespace PySideCPP2

#endif // TESTOBJECT_H

