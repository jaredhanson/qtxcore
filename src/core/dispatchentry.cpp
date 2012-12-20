#include "dispatchentry.h"


DispatchEntry::DispatchEntry(const QObject *sender, const QString & signal, QObject *receiver, const char *slot)
    : mSender(sender),
      mSignal(signal),
      mReceiver(receiver),
      mSlot(0)
{
    mSlot = qstrdup(slot);
}

DispatchEntry::~DispatchEntry()
{
    if (mSlot) {
        delete[] mSlot;
        mSlot = 0;
    }
}

const QObject *DispatchEntry::sender() const
{
    return mSender;
}

QString DispatchEntry::signal() const
{
    return mSignal;
}

QObject *DispatchEntry::receiver() const
{
    return mReceiver;
}

const char* DispatchEntry::slot() const
{
    return mSlot;
}
