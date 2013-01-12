#include "dispatchentry.h"

QTX_BEGIN_NAMESPACE


DispatchEntry::DispatchEntry(const QObject *poster, const QString & notification, QObject *observer, const char *method)
    : mSender(poster),
      mSignal(notification),
      mReceiver(observer),
      mSlot(0)
{
    mSlot = qstrdup(method);
}

DispatchEntry::~DispatchEntry()
{
    if (mSlot) {
        delete[] mSlot;
        mSlot = 0;
    }
}

const QObject *DispatchEntry::poster() const
{
    return mSender;
}

QString DispatchEntry::notification() const
{
    return mSignal;
}

QObject *DispatchEntry::observer() const
{
    return mReceiver;
}

const char* DispatchEntry::method() const
{
    return mSlot;
}


QTX_END_NAMESPACE
