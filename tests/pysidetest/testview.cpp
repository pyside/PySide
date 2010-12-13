#include "testview.h"
#include <QDebug>
#include <stdio.h>

QObject*
TestView::getData()
{
    QModelIndex index;
    QVariant data = m_model->data(index);
    QObject* obj = 0;
    if (data.canConvert<QObject*>())
        obj = data.value<QObject*>();
    return obj;
}

