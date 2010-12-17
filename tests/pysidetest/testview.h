#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QObject>
#ifdef pysidetest_EXPORTS
#define PYSIDE_EXPORTS 1
#endif
#include "pysidemacros.h"

class QWidget;
class QAbstractListModel;
class QAbstractItemDelegate;

class PYSIDE_API TestView : public QObject
{
    Q_OBJECT
public:
    TestView(QAbstractListModel* model, QObject* parent = 0) : QObject(parent), m_model(model) {}
    QAbstractListModel* model() { return m_model; }
    QVariant getData();

    void setItemDelegate(QAbstractItemDelegate* delegate) { m_delegate = delegate; }
    QWidget* getEditorWidgetFromItemDelegate() const;

private:
    QAbstractListModel* m_model;
    QAbstractItemDelegate* m_delegate;
};

#endif // TESTVIEW_H

