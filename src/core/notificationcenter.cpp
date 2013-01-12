#include "notificationcenter.h"
#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


/*!
    \class NotificationCenter
    \inmodule QtxCore
    \brief The NotificationCenter class provides a mechanism for dispatching
           notifications within an application.
 */


/*!
    Returns a pointer to the application's default NotificationCenter instance.
*/
NotificationCenter* NotificationCenter::instance()
{
    static NotificationCenter *center = 0;
    if (!center) {
        center = new NotificationCenter();
    }
    return center;
}

/*!
    Constructs a NotificationCenter object with the given \a parent.
*/
NotificationCenter::NotificationCenter(QObject *parent /* = 0 */)
    : QObject(parent),
      mPoster(0)
{
}

/*!
    Destroy the object.
*/
NotificationCenter::~NotificationCenter()
{
}

void NotificationCenter::observe(QObject *observer, const char *method)
{
    observe(0, "", observer, method);
}

/*!
    TODO: \a signal \a receiver \a slot
*/
void NotificationCenter::observe(const QString & notification, QObject *observer, const char *method)
{
    observe(0, notification, observer, method);
}

void NotificationCenter::observe(const QObject *poster, QObject *observer, const char *method)
{
    observe(poster, "", observer, method);
}

/*!
    TODO: \a sender \a signal \a receiver \a slot
*/
void NotificationCenter::observe(const QObject *poster, const QString & notification,
                                 QObject *observer, const char *method)
{
    DispatchEntry *entry = new DispatchEntry(poster, notification, observer, method);
    mDispatchTable.append(entry);
    
    QObject::connect(observer, SIGNAL(destroyed(QObject *)), SLOT(onDestroyed(QObject *)));
}

/*!
    TODO: \a receiver
*/
void NotificationCenter::unobserve(const QObject *observer)
{
    unobserve(0, "", observer);
}

/*!
    TODO: \a sender \a signal \a receiver
*/
void NotificationCenter::unobserve(const QObject *poster, const QString & notification, const QObject *observer)
{
    QMutableListIterator<DispatchEntry *> itr(mDispatchTable);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if (entry->observer() == observer
            && (entry->poster() == poster || !poster)
            && (entry->notification() == notification || notification.isEmpty())) {
            itr.remove();
        }
    }
}

/*!
    TODO: \a sender \a signal \a val0 \a val1 \a val2 \a val3 \a val4 \a val5 \a val6 \a val7 \a val8 \a val9
*/
void NotificationCenter::post(QObject *poster, const QString & notification,
                              QGenericArgument val0 /* = QGenericArgument( 0 ) */, QGenericArgument val1 /* = QGenericArgument() */, QGenericArgument val2 /* = QGenericArgument() */, QGenericArgument val3 /* = QGenericArgument() */, QGenericArgument val4 /* = QGenericArgument() */, QGenericArgument val5 /* = QGenericArgument() */, QGenericArgument val6 /* = QGenericArgument() */, QGenericArgument val7 /* = QGenericArgument() */, QGenericArgument val8 /* = QGenericArgument() */, QGenericArgument val9 /* = QGenericArgument() */)
{
    mPoster = poster;
    
    QList<DispatchEntry *> table(mDispatchTable);
    QMutableListIterator<DispatchEntry *> itr(table);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if ((entry->poster() == poster || !entry->poster())
            && (entry->notification() == notification || entry->notification().isEmpty())) {
            
            QObject *observer = entry->observer();
            const char *method = entry->method();
            const QMetaObject* metaObserver = observer->metaObject();
            int idx = metaObserver->indexOfSlot(method);
            if (idx == -1) {
                continue;
            }
            QMetaMethod metaMethod = metaObserver->method(idx);
            metaMethod.invoke(observer, Qt::DirectConnection, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
        }
    }

    mPoster = 0;
}


/*!
    TODO:
*/
QObject *NotificationCenter::poster() const
{
    return mPoster;
}

void NotificationCenter::onDestroyed(QObject * obj /* = 0 */)
{
    if (!obj) {
        return;
    }
    
    unobserve(obj);
}


QTX_END_NAMESPACE
