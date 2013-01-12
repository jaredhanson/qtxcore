#ifndef DISPATCHENTRY_H
#define DISPATCHENTRY_H

#include "coreglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class DispatchEntry
{
public:
    DispatchEntry(const QObject *poster, const QString & notification, QObject *observer, const char *method);
    ~DispatchEntry();

    const QObject *poster() const;
    QString notification() const;

    QObject *observer() const;
    const char *method() const;
        
private:
    const QObject *mSender;
    QString mSignal;
    QObject *mReceiver;
    char *mSlot;
};


QTX_END_NAMESPACE

#endif // SIGNALCENTER_H
