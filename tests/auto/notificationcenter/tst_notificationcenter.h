#ifndef TST_NOTIFICATIONCENTER_H
#define TST_NOTIFICATIONCENTER_H

#include "notificationcenter.h"
#include "../../mock/src/mockposter.h"
#include "../../mock/src/mockobserver.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_NotificationCenter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void observeSpecificPosterAndNotification();
    
    void unobserveSpecificPosterAndNotification();
    
private:
    NotificationCenter *mNotificationCenter;
    MockPoster *mPoster;
};

#endif // TST_NOTIFICATIONCENTER_H
