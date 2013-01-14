#ifndef QTXCORE_DISPATCHENTRY_H
#define QTXCORE_DISPATCHENTRY_H

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
    const QObject *mPoster;
    QString mNotification;
    QObject *mObserver;
    char *mMethod;
};


QTX_END_NAMESPACE

#endif // QTXCORE_DISPATCHENTRY_H
