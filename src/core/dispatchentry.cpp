#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


DispatchEntry::DispatchEntry(const QObject *poster, const QString & notification, QObject *observer, const char *method)
    : mPoster(poster),
      mNotification(notification),
      mObserver(observer),
      mMethod(0)
{
    mMethod = qstrdup(method);
}

DispatchEntry::~DispatchEntry()
{
    if (mMethod) {
        delete[] mMethod;
        mMethod = 0;
    }
}

const QObject *DispatchEntry::poster() const
{
    return mPoster;
}

QString DispatchEntry::notification() const
{
    return mNotification;
}

QObject *DispatchEntry::observer() const
{
    return mObserver;
}

const char *DispatchEntry::method() const
{
    return mMethod;
}


QTX_END_NAMESPACE
