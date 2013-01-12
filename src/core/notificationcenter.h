#ifndef QTXCORE_NOTIFICATIONCENTER_H
#define QTXCORE_NOTIFICATIONCENTER_H

#include "coreglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class DispatchEntry;

class NotificationCenter : public QObject
{
    Q_OBJECT
    
public:
    static NotificationCenter *instance();

public:
    NotificationCenter(QObject *parent = 0);
    ~NotificationCenter();

    void observe(QObject *observer, const char *method);
    void observe(const QString & notification, QObject *observer, const char *method);
    void observe(const QObject *poster, QObject *observer, const char *method);
    void observe(const QObject *poster, const QString & notification, QObject *observer, const char *method);
    
    void unobserve(const QObject *observer);
    void unobserve(const QObject *poster, const QString & notification, const QObject *observer);

    void post(QObject *poster, const QString & notification,
              QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument());

    QObject *poster() const;

private slots:
    void onDestroyed(QObject *obj = 0);
    
private:
    QList<DispatchEntry *> mDispatchTable;

    QObject *mPoster;
};


QTX_END_NAMESPACE

#endif // QTXCORE_NOTIFICATIONCENTER_H
