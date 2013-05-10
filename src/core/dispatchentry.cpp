#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


/*!
    \class DispatchEntry
    \inmodule QtxCore
    \internal
    
    \brief The DispatchEntry class represents an entry in a NotificationCenter's
           dispatch table.
 */


/*!
    Constructs an entry for \a poster and \a notification to \a observer and \a method.
*/
DispatchEntry::DispatchEntry(const QObject *poster, const QString & notification, QObject *observer, const char *method)
    : mPoster(poster),
      mNotification(notification),
      mObserver(observer),
      mMethod(0)
{
    mMethod = qstrdup(method);
}

/*!
    Destroys the entry.
*/
DispatchEntry::~DispatchEntry()
{
    if (mMethod) {
        delete[] mMethod;
        mMethod = 0;
    }
}

/*!
    Returns the poster registered for this entry.
*/
const QObject *DispatchEntry::poster() const
{
    return mPoster;
}

/*!
    Returns the notification registered for this entry.
*/
QString DispatchEntry::notification() const
{
    return mNotification;
}

/*!
    Returns the observer registered for this entry.
*/
QObject *DispatchEntry::observer() const
{
    return mObserver;
}

/*!
    Returns the observer's method registered for this entry.
*/
const char *DispatchEntry::method() const
{
    return mMethod;
}


QTX_END_NAMESPACE
