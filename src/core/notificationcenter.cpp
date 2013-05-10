#include "notificationcenter.h"
#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


class NotificationCenterPrivate
{
public:
    NotificationCenterPrivate();
    ~NotificationCenterPrivate();
    
    QList<DispatchEntry *> dispatchTable;
    QObject *poster;
};


/*!
    \class NotificationCenter
    \inmodule QtxCore
    
    \brief The NotificationCenter class provides a mechanism for dispatching
           notifications within an application.
    
    A notification center is similiar to Qt's signals and slots, but are
    decoupled from the objects themselves.  In order to connect to a signal, a
    reference to the emitting object must first be obtained.  In contrast, a
    notification center serves as an application-wide bus, allowing independent
    subsystems to communicate using only a reference to a common notification
    center.
 */


/*!
    Returns a pointer to the application's default NotificationCenter instance.
*/
NotificationCenter *NotificationCenter::instance()
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
      d_ptr(new NotificationCenterPrivate())
{
}

/*!
    Destroys the object.
*/
NotificationCenter::~NotificationCenter()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

/*!
    Add an \a observer for all notifications from all posters which will invoke \a method.
*/
void NotificationCenter::observe(QObject *observer, const char *method)
{
    observe(0, "", observer, method);
}

/*!
    Add an \a observer for \a notification from any poster which will invoke \a method.
*/
void NotificationCenter::observe(const QString & notification, QObject *observer, const char *method)
{
    observe(0, notification, observer, method);
}

/*!
    Add an \a observer for any notification from \a poster which will invoke \a method.
*/
void NotificationCenter::observe(const QObject *poster, QObject *observer, const char *method)
{
    observe(poster, "", observer, method);
}

/*!
    Add an \a observer for the given \a notification from \a poster which will invoke \a method.
*/
void NotificationCenter::observe(const QObject *poster, const QString & notification,
                                 QObject *observer, const char *method)
{
    DispatchEntry *entry = new DispatchEntry(poster, notification, observer, method);
    d_ptr->dispatchTable.append(entry);
    
    QObject::connect(observer, SIGNAL(destroyed(QObject *)), SLOT(onDestroyed(QObject *)));
}

/*!
    Remove \a observer for all notifications from any poster.
*/
void NotificationCenter::unobserve(const QObject *observer)
{
    unobserve(0, "", observer);
}

/*!
    Remove \a observer for \a notification from any poster.
*/
void NotificationCenter::unobserve(const QString & notification, const QObject *observer)
{
    unobserve(0, notification, observer);
}

/*!
    Remove \a observer for all notifications from \a poster.
*/
void NotificationCenter::unobserve(const QObject *poster, const QObject *observer)
{
    unobserve(poster, "", observer);
}

/*!
    Remove \a observer for \a notification from \a poster.
*/
void NotificationCenter::unobserve(const QObject *poster, const QString & notification, const QObject *observer)
{
    QMutableListIterator<DispatchEntry *> itr(d_ptr->dispatchTable);
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
    Post \a notification from \a poster.
    
    You can pass up to ten arguments (\a val0, \a val1, \a val2, \a val3,
    \a val4, \a val5, \a val6, \a val7, \a val8, and \a val9) to this method
    call.
*/
void NotificationCenter::post(QObject *poster, const QString & notification,
                              QGenericArgument val0 /* = QGenericArgument( 0 ) */, QGenericArgument val1 /* = QGenericArgument() */, QGenericArgument val2 /* = QGenericArgument() */, QGenericArgument val3 /* = QGenericArgument() */, QGenericArgument val4 /* = QGenericArgument() */, QGenericArgument val5 /* = QGenericArgument() */, QGenericArgument val6 /* = QGenericArgument() */, QGenericArgument val7 /* = QGenericArgument() */, QGenericArgument val8 /* = QGenericArgument() */, QGenericArgument val9 /* = QGenericArgument() */)
{
    d_ptr->poster = poster;
    
    QList<DispatchEntry *> table(d_ptr->dispatchTable);
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

    d_ptr->poster = 0;
}

/*!
    Returns a pointer to the object that posted the notification.
*/
QObject *NotificationCenter::poster() const
{
    return d_ptr->poster;
}

void NotificationCenter::onDestroyed(QObject * obj /* = 0 */)
{
    if (!obj) {
        return;
    }
    
    unobserve(obj);
}


NotificationCenterPrivate::NotificationCenterPrivate()
{
}

NotificationCenterPrivate::~NotificationCenterPrivate()
{
    for (int i = 0; i < dispatchTable.size(); i++) {
        delete dispatchTable.at(i);
    }
}


QTX_END_NAMESPACE
