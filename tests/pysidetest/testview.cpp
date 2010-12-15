#include "testview.h"
#include <QDebug>
#include <stdio.h>

QVariant
TestView::getData()
{
    QModelIndex index;
    QVariant data = m_model->data(index);
    return data;
}

