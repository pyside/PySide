#include "testview.h"

#include <QWidget>
#include <QAbstractListModel>
#include <QAbstractItemDelegate>

QVariant
TestView::getData()
{
    QModelIndex index;
    return m_model->data(index);
}

QWidget*
TestView::getEditorWidgetFromItemDelegate() const
{
    if (!m_delegate)
        return 0;

    QModelIndex index;
    QStyleOptionViewItem options;
    return m_delegate->createEditor(0, options, index);
}

