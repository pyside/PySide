#ifndef PYSIDE_DESTROY_LISTENER
#define PYSIDE_DESTROY_LISTENER


#include <QObject>
#include "pysidemacros.h"

namespace PySide
{
class DestroyListenerPrivate;
class PYSIDE_API DestroyListener : public QObject
{
    Q_OBJECT
    public:
        static DestroyListener* instance();
        static void destroy();
        void listen(QObject* obj);

    public slots:
        void onObjectDestroyed(QObject* obj);

    private:
        static DestroyListener* m_instance;
        DestroyListenerPrivate* m_d;
        DestroyListener(QObject *parent);
        ~DestroyListener();
};

}//namespace

#endif

