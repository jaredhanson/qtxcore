#include "notificationcenter.h"
#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


/*!
    \class SignalCenter
    \inmodule QtxCore
    \brief The SignalCenter class provides a mechanism for dispatching
           notifications within an application.
 */


/*!
    Returns a pointer to the application's default SignalCenter instance.
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
    Constructs a SignalCenter object with the given \a parent.
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
void NotificationCenter::observe(const QString & signal, QObject *receiver, const char *slot)
{
    observe(0, signal, receiver, slot);
}

/*!
    TODO: \a sender \a signal \a receiver \a slot
*/
void NotificationCenter::observe(const QObject *sender, const QString & signal,
                           QObject *receiver, const char *slot)
{
    DispatchEntry *entry = new DispatchEntry(sender, signal, receiver, slot);
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
void NotificationCenter::unobserve(const QObject *sender, const QString & signal, const QObject *receiver)
{
    QMutableListIterator<DispatchEntry *> itr(mDispatchTable);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if (entry->receiver() == receiver
            && (entry->sender() == sender || !sender)
            && (entry->signal() == signal || signal.isEmpty())) {
            itr.remove();
        }
    }
}

/*!
    TODO: \a sender \a signal \a val0 \a val1 \a val2 \a val3 \a val4 \a val5 \a val6 \a val7 \a val8 \a val9
*/
void NotificationCenter::post(QObject *sender, const QString & signal,
                              QGenericArgument val0 /* = QGenericArgument( 0 ) */, QGenericArgument val1 /* = QGenericArgument() */, QGenericArgument val2 /* = QGenericArgument() */, QGenericArgument val3 /* = QGenericArgument() */, QGenericArgument val4 /* = QGenericArgument() */, QGenericArgument val5 /* = QGenericArgument() */, QGenericArgument val6 /* = QGenericArgument() */, QGenericArgument val7 /* = QGenericArgument() */, QGenericArgument val8 /* = QGenericArgument() */, QGenericArgument val9 /* = QGenericArgument() */)
{
    mPoster = sender;
    
    QList<DispatchEntry *> table(mDispatchTable);
    QMutableListIterator<DispatchEntry *> itr(table);
    while (itr.hasNext()) {
        DispatchEntry* entry = itr.next();
        if ((entry->sender() == sender || !entry->sender())
            && (entry->signal() == signal || entry->signal().isEmpty())) {
            
            QObject *receiver = entry->receiver();
            const char *slot = entry->slot();
            const QMetaObject* metaReceiver = receiver->metaObject();
            int idx = metaReceiver->indexOfSlot(slot);
            if (idx == -1) {
                continue;
            }
            QMetaMethod method = metaReceiver->method(idx);
            method.invoke(receiver, Qt::DirectConnection, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
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
