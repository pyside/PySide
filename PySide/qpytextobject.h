#ifndef QPYTEXTOBJECT
#define QPYTEXTOBJECT

#include <QObject>
#include <QTextObjectInterface>

class QPyTextObject : public QObject, public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:
    QPyTextObject(QObject* parent = 0) : QObject(parent) {}
    void drawObject(QPainter* painter, const QRectF& rect, QTextDocument* doc, int posInDocument, const QTextFormat& format ) = 0;
    QSizeF intrinsicSize(QTextDocument* doc, int posInDocument, const QTextFormat& format ) = 0;
};
#endif