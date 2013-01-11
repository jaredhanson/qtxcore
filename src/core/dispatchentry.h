#ifndef DISPATCHENTRY_H
#define DISPATCHENTRY_H

#include "coreglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class DispatchEntry
{
public:
    DispatchEntry(const QObject *sender, const QString & signal, QObject* receiver, const char* slot);
    ~DispatchEntry();

    const QObject *sender() const;
    QString notification() const;

    QObject *receiver() const;
    const char *method() const;
        
private:
    const QObject *mSender;
    QString mSignal;
    QObject *mReceiver;
    char *mSlot;
};


QTX_END_NAMESPACE

#endif // SIGNALCENTER_H
