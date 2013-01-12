#ifndef MOCK_MOCKOBSERVER_H
#define MOCK_MOCKOBSERVER_H

#include "notificationcenter.h"
#include <QtCore>

QTX_USE_NAMESPACE


class MockObserver : public QObject
{
    Q_OBJECT

public:
    MockObserver();
    ~MockObserver();
    
    void observe();
    void observe(const QString & notification);
    void observe(const QObject *poster);
    void observe(const QObject *poster, const QString & notification);
    void unobserve(const QObject *poster, const QString & notification);
    
    int count() const;
    
    void setNotificationCenter(NotificationCenter *center);
    
private slots:
    void onNotification();
    
private:
    NotificationCenter *mNotificationCenter;
    int mCount;
};

#endif // MOCK_MOCKOBSERVER_H