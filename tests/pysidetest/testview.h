#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QObject>
#include <QAbstractListModel>
#ifdef pysidetest_EXPORTS
#define PYSIDE_EXPORTS 1
#endif
#include "pysidemacros.h"

class PYSIDE_API TestView : public QObject
{
    Q_OBJECT
public:
    TestView(QAbstractListModel* model, QObject* parent = 0) : QObject(parent), m_model(model) {}
    QAbstractListModel* model() { return m_model; }
    QVariant getData();
private:
    QAbstractListModel* m_model;
};

#endif // TESTVIEW_H

