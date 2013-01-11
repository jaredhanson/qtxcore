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

/*!
    TODO: \a signal \a receiver \a slot
*/
void NotificationCenter::observe(const QString & notification, QObject *receiver, const char *method)
{
    observe(0, notification, receiver, method);
}

/*!
    TODO: \a sender \a signal \a receiver \a slot
*/
void NotificationCenter::observe(const QObject *sender, const QString & notification,
                                 QObject *receiver, const char *method)
{
    DispatchEntry *entry = new DispatchEntry(sender, notification, receiver, method);
    mDispatchTable.append(entry);
    
    QObject::connect(receiver, SIGNAL(destroyed(QObject *)), SLOT(onDestroyed(QObject *)));
}

/*!
    TODO: \a receiver
*/
void NotificationCenter::unobserve(const QObject *receiver)
{
    unobserve(0, "", receiver);
}

/*!
    TODO: \a sender \a signal \a receiver
*/
void NotificationCenter::unobserve(const QObject *sender, const QString & notification, const QObject *receiver)
{
    QMutableListIterator<DispatchEntry *> itr(mDispatchTable);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if (entry->receiver() == receiver
            && (entry->sender() == sender || !sender)
            && (entry->notification() == notification || notification.isEmpty())) {
            itr.remove();
        }
    }
}

/*!
    TODO: \a sender \a signal \a val0 \a val1 \a val2 \a val3 \a val4 \a val5 \a val6 \a val7 \a val8 \a val9
*/
void NotificationCenter::post(QObject *sender, const QString & notification,
                              QGenericArgument val0 /* = QGenericArgument( 0 ) */, QGenericArgument val1 /* = QGenericArgument() */, QGenericArgument val2 /* = QGenericArgument() */, QGenericArgument val3 /* = QGenericArgument() */, QGenericArgument val4 /* = QGenericArgument() */, QGenericArgument val5 /* = QGenericArgument() */, QGenericArgument val6 /* = QGenericArgument() */, QGenericArgument val7 /* = QGenericArgument() */, QGenericArgument val8 /* = QGenericArgument() */, QGenericArgument val9 /* = QGenericArgument() */)
{
    mPoster = sender;
    
    QList<DispatchEntry *> table(mDispatchTable);
    QMutableListIterator<DispatchEntry *> itr(table);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if ((entry->sender() == sender || !entry->sender())
            && (entry->notification() == notification || entry->notification().isEmpty())) {
            
            QObject *receiver = entry->receiver();
            const char *method = entry->method();
            const QMetaObject* metaReceiver = receiver->metaObject();
            int idx = metaReceiver->indexOfSlot(method);
            if (idx == -1) {
                continue;
            }
            QMetaMethod metaMethod = metaReceiver->method(idx);
            metaMethod.invoke(receiver, Qt::DirectConnection, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
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
