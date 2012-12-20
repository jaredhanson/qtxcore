#ifndef DISPATCHENTRY_H
#define DISPATCHENTRY_H

#include <QtCore>


class DispatchEntry
{
public:
    DispatchEntry(const QObject *sender, const QString & signal, QObject* receiver, const char* slot);
    ~DispatchEntry();

    const QObject *sender() const;
    QString signal() const;

    QObject *receiver() const;
    const char *slot() const;
        
private:
    const QObject *mSender;
    QString mSignal;
    QObject *mReceiver;
    char *mSlot;
};

#endif // SIGNALCENTER_H
