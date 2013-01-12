#ifndef TST_NOTIFICATIONCENTER_H
#define TST_NOTIFICATIONCENTER_H

#include "notificationcenter.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_NotificationCenter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void observeAnyPosterAndAnyNotification();
    void observeAnyPosterAndSpecificNotification();
    void observeSpecificPosterAndAnyNotification();
    void observeSpecificPosterAndSpecificNotification();
    
    void unobserveSpecificPosterAndSpecificNotification();
    
private:
    NotificationCenter *mNotificationCenter;
};

#endif // TST_NOTIFICATIONCENTER_H
